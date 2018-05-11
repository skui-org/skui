/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2018 Ruben Van Boxem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "gui/events/xcb.h++"

#include "gui/native_window/xcb.h++"
#include "gui/window.h++"

#include <core/debug.h++>

namespace skui
{
  namespace gui
  {
    namespace events
    {
      xcb::xcb(gui::window& window)
        : base(window)
      {
        auto native_xcb_window = dynamic_cast<native_window::xcb*>(&window.get_native_window());
        if(!native_xcb_window)
          core::debug_print("events::xcb requires a native_window::xcb or native_window::xlib.\n");

        connection = native_xcb_window->get_connection();
        xcb_window = native_xcb_window->get_window();

        // The magic incantation to receive and be able to check for the "window was closed" event
        xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");
        core::unique_free_ptr<xcb_intern_atom_reply_t> reply(xcb_intern_atom_reply(connection, cookie, nullptr));

        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
        wm_delete_window.reset(xcb_intern_atom_reply(connection, cookie2, nullptr));

        xcb_change_property(connection,
                            XCB_PROP_MODE_REPLACE,
                            xcb_window,
                            reply->atom, 4, 32, 1, &wm_delete_window->atom);
        // end magic

        xcb_flush(connection);
      }

      xcb::~xcb() = default;

      void xcb::exec()
      {
        bool running = true;

        while(running)
        {
          core::unique_free_ptr<xcb_generic_event_t> event_ptr(xcb_wait_for_event(connection));
          if(!event_ptr)
          {
            core::debug_print("Call to xcb_wait_for_event failed. Most likely an I/O error.\n");
            running = false;
            break;
          }

          switch(event_ptr->response_type & ~0x80)
          {
            case XCB_EXPOSE:
            {
              auto expose = reinterpret_cast<xcb_expose_event_t*>(event_ptr.get());
              if(expose->count>0)
                continue;

              window.repaint();

              break;
            }
            case XCB_UNMAP_NOTIFY:
            {
              //auto unmap = reinterpret_cast<xcb_unmap_notify_event_t*>(event_ptr.get());
              break;
            }
            case XCB_BUTTON_PRESS:
            {
              auto button_press = reinterpret_cast<xcb_button_press_event_t*>(event_ptr.get());

              switch (button_press->state)
              {
                case XCB_BUTTON_MASK_1:
                  core::debug_print("Primary mouse button pressed.");
                  break;
              }

              switch (button_press->detail)
              {
                case 4:
                  // Wheel button up
                  break;
                case 5:
                  // wheel button down
                  break;
                default:
                  core::debug_print("Button ", button_press->detail, " pressed in window ", button_press->event, ", at coordinates (", button_press->event_x, ",", button_press->event, ").\n");
                  break;
              }
              break;
            }
            case XCB_BUTTON_RELEASE:
            {
              //auto button_release = reinterpret_cast<xcb_button_release_event_t*>(event_ptr.get());
              //implementation::print_modifiers(button_release->state);
              break;
            }
            case XCB_MOTION_NOTIFY:
            {
              //auto motion = reinterpret_cast<xcb_motion_notify_event_t*>(event_ptr.get());
              break;
            }
            case XCB_ENTER_NOTIFY:
            {
              //auto enter = reinterpret_cast<xcb_enter_notify_event_t*>(event_ptr.get());
              break;
            }
            case XCB_LEAVE_NOTIFY:
            {
              //auto leave = reinterpret_cast<xcb_leave_notify_event_t*>(event_ptr.get());
              break;
            }
            case XCB_KEY_PRESS:
            {
              //auto key_press = reinterpret_cast<xcb_key_press_event_t*>(event_ptr.get());
              //implementation::print_modifiers(key_press->state);
              break;
            }
            case XCB_KEY_RELEASE:
            {
              //auto key_release = reinterpret_cast<xcb_key_release_event_t*>(event_ptr.get());
              //implementation::print_modifiers(key_release->state);
              break;
            }
            case XCB_CONFIGURE_NOTIFY:
            {
              // We send out an event here so when maximizing or minimizing a window, it gets repainted properly
              const auto& configure_notify = *reinterpret_cast<xcb_configure_notify_event_t*>(event_ptr.get());
              // xcb_send_event is hardcoded to read 32 bytes regardless the event type, so give it 32 bytes.
              core::unique_free_ptr<xcb_expose_event_t> event(reinterpret_cast<xcb_expose_event_t*>(std::calloc(1, 32)));
              event->response_type = XCB_EXPOSE;
              event->window = xcb_window;
              event->x = static_cast<std::uint16_t>(configure_notify.x);
              event->y = static_cast<std::uint16_t>(configure_notify.y);
              event->width = configure_notify.width;
              event->height = configure_notify.height;

              xcb_send_event(connection, false, xcb_window, XCB_EVENT_MASK_EXPOSURE, reinterpret_cast<char*>(event.get()));
              xcb_flush(connection);

              break;
            }
            case XCB_CLIENT_MESSAGE:
            {
              auto client_message = reinterpret_cast<xcb_client_message_event_t*>(event_ptr.get());

              if(client_message->data.data32[0] == wm_delete_window->atom)
              {
                core::debug_print("WM_DELETE_WINDOW received.\n");
                window.close();
              }
              break;
            }
            case XCB_DESTROY_NOTIFY:
            {
              running = false;
              break;
            }
            default:
              core::debug_print("Unknown event: ", event_ptr->response_type & ~0x80, ".\n");
              break;
          }
        }
      }
    }
  }
}
