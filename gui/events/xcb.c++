/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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
#include "gui/native_window/xlib.h++"
#include "gui/window.h++"

#include <core/debug.h++>

namespace
{
  using namespace skui::gui::input;

  std::uint8_t mask_send_event_bit(std::uint8_t response_type)
  {
    return response_type & 0b0111'1111;
  }

  std::optional<button> get_button(xcb_button_t xcb_button)
  {
    switch(xcb_button)
    {
      case 1:
        return button::primary;
      case 2:
        return button::middle;
      case 3:
        return button::secondary;
      default:
        return {};
    }
  }

  std::optional<scroll> get_scroll(xcb_button_t xcb_button)
  {
    switch(xcb_button)
    {
      case 4:
        return scroll::up;
      case 5:
        return scroll::down;
      case 6:
        return scroll::left; //?
      case 7:
        return scroll::right; //?
      default:
        return {};
    }
  }
}

namespace skui::gui::events
{
  xcb::xcb(gui::window& window)
    : base{window}
  {
    auto native_xcb_window = dynamic_cast<native_window::xcb*>(&window.get_native_window());
    if(!native_xcb_window)
      core::debug_print("events::xcb requires a native_window::xcb or native_window::xlib.\n");

    connection = native_xcb_window->get_connection();
    xcb_window = native_xcb_window->get_window();

    // The magic incantation to receive and be able to check for the "window was closed" event
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, true, 12, "WM_PROTOCOLS");
    core::unique_free_ptr<xcb_intern_atom_reply_t> reply(xcb_intern_atom_reply(connection, cookie, nullptr));

    xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(connection, false, 16, "WM_DELETE_WINDOW");
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
      core::unique_free_ptr<const xcb_generic_event_t> event_ptr(xcb_wait_for_event(connection));
      if(!event_ptr)
      {
        core::debug_print("Call to xcb_wait_for_event failed. Most likely an I/O error.\n");
        running = false;
        break;
      }

      switch(mask_send_event_bit(event_ptr->response_type))
      {
        case XCB_EXPOSE:
        {
          const auto& expose = reinterpret_cast<const xcb_expose_event_t&>(*event_ptr);
          if(expose.count>0)
            continue;

          window.update();

          break;
        }
        case XCB_UNMAP_NOTIFY:
        {
          //const auto& unmap = reinterpret_cast<const xcb_unmap_notify_event_t&>(*event_ptr);
          break;
        }
        case XCB_MAP_NOTIFY:
        {
          //const auto& map = reinterpret_cast<const xcb_map_notify_event_t&>(*event_ptr);
          window.state = window_state::windowed;

          break;
        }
        case XCB_BUTTON_PRESS:
        {
          const auto& button_press = reinterpret_cast<const xcb_button_press_event_t&>(*event_ptr);

          const graphics::pixel_position position{button_press.event_x,
                                                  button_press.event_y};

          if(const auto button = get_button(button_press.detail); button)
          {
            pressed_buttons.set(*button);

            window.pointer.pressed(*button, position);
          }
          else if(const auto scroll = get_scroll(button_press.detail); scroll)
          {
            window.pointer.scroll(*scroll, position);
          }

          break;
        }
        case XCB_BUTTON_RELEASE:
        {
          const auto& button_release = reinterpret_cast<const xcb_button_release_event_t&>(*event_ptr);

          const graphics::pixel_position position{button_release.event_x,
                                                  button_release.event_y};

          if(const auto button = get_button(button_release.detail); button)
          {
            const bool click = pressed_buttons.test(*button);
            pressed_buttons.unset(*button);

            window.pointer.released(*button, position);
            if(click)
              window.pointer.clicked(*button, position);
          }

          break;
        }
        case XCB_MOTION_NOTIFY:
        {
          const auto& motion = reinterpret_cast<const xcb_motion_notify_event_t&>(*event_ptr);

          const graphics::pixel_position position{motion.event_x,
                                                  motion.event_y};
          window.pointer.moved(position);

          break;
        }
        case XCB_ENTER_NOTIFY:
        {
          const auto& enter = reinterpret_cast<const xcb_enter_notify_event_t&>(*event_ptr);

          const graphics::pixel_position position{enter.event_x,
                                                  enter.event_y};
          window.pointer.entered(position);

          break;
        }
        case XCB_LEAVE_NOTIFY:
        {
          const auto& leave = reinterpret_cast<const xcb_leave_notify_event_t&>(*event_ptr);

          const graphics::pixel_position position{leave.event_x,
                                                  leave.event_y};
          window.pointer.left(position);

          break;
        }
        case XCB_KEY_PRESS:
        {
          //const auto& key_press = reinterpret_cast<xcb_key_press_event_t&>(*event_ptr);
          //implementation::print_modifiers(key_press->state);
          break;
        }
        case XCB_KEY_RELEASE:
        {
          //const auto& key_release = reinterpret_cast<xcb_key_release_event_t*>(*event_ptr);
          //implementation::print_modifiers(key_release->state);
          break;
        }
        case XCB_CONFIGURE_NOTIFY:
        {
          const auto& configure_notify = reinterpret_cast<const xcb_configure_notify_event_t&>(*event_ptr);

          window.size = {configure_notify.width, configure_notify.height};
          window.position = {configure_notify.x, configure_notify.y};

          break;
        }
        case XCB_CLIENT_MESSAGE:
        {
          const auto& client_message = reinterpret_cast<const xcb_client_message_event_t&>(*event_ptr);

          if(client_message.data.data32[0] == wm_delete_window->atom)
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
        case XCB_REPARENT_NOTIFY:
        {
          //const auto& reparent = reinterpret_cast<const xcb_reparent_notify_event_t&>(*event_ptr);

          break;
        }
        default:
          if(const auto* xlib_window = dynamic_cast<native_window::xlib*>(&window.get_native_window());
             xlib_window)
          {
            xlib_window->handle_dri2_events(const_cast<xcb_generic_event_t&>(*event_ptr));
            break;
          }
          core::debug_print("Unknown event: ", static_cast<int>(mask_send_event_bit(event_ptr->response_type)), ".\n");
          break;
      }
    }
  }
}
