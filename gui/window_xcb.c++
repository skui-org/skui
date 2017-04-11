/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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

/*
 * Implementation based on Khronos examples at
 * https://www.khronos.org/opengl/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib
 * https://www.khronos.org/opengl/wiki/Tutorial:_OpenGL_3.0_Context_Creation_(GLX)
 */

#include "gui/window.h++"

#include <core/application.h++>
#include <core/debug.h++>

#include <graphics/skia_gl_context.h++>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>

#include <GL/glx.h> // TODO: split this off into a separable entity

#include <iostream>

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
      struct xdisplay_deleter { void operator()(Display* d) const { XCloseDisplay(d); } };
      template<typename XFreeable>
      struct xfree_deleter { void operator()(XFreeable* resource) const { XFree(resource); } };

      using xdisplay_ptr = std::unique_ptr<Display, xdisplay_deleter>;
      using xvisualinfo_ptr = std::unique_ptr<XVisualInfo, xfree_deleter<XVisualInfo>>;
      using xstring_ptr = std::unique_ptr<char, xfree_deleter<char>>;
      using xcb_intern_atom_reply_ptr = core::unique_free_ptr<xcb_intern_atom_reply_t>;

      class platform_handle
      {
      public:
        platform_handle()
          : display(nullptr)
          , connection(nullptr)
          , wm_delete_window(nullptr)
          , visual_info(nullptr)
          , context(nullptr)
          , id(0)
        {}

        ~platform_handle()
        {
          core::debug_print("Freeing X resources.\n");
          if(context)
            glXDestroyContext(display.get(), context);
        }

        xdisplay_ptr display;
        xcb_connection_t* connection;
        xcb_intern_atom_reply_ptr wm_delete_window;
        xvisualinfo_ptr visual_info;
        GLXContext context;
        xcb_window_t id; // synonymous with Xlib's Window
      };

      void platform_handle_deleter::operator()(platform_handle* handle) const
      {
        delete handle;
      }

      platform_handle_ptr create_handle()
      {
        platform_handle_ptr handle(new platform_handle);

        // Open Display connection
        handle->display.reset(XOpenDisplay(nullptr));
        if(!handle->display)
        {
          core::debug_print("Call to XOpenDisplay failed.");
          return nullptr;
        }

        // Handover to XCB for event handling
        handle->connection = XGetXCBConnection(handle->display.get());
        XSetEventQueueOwner(handle->display.get(), XCBOwnsEventQueue);

        return handle;
      }

      void print_modifiers(std::uint32_t mask)
      {
        const char **mod, *mods[] = {
          "Shift", "Lock", "Ctrl", "Alt",
          "Mod2", "Mod3", "Mod4", "Mod5",
          "Button1", "Button2", "Button3", "Button4", "Button5"
        };
        printf ("Modifier mask: ");
        for (mod = mods ; mask; mask >>= 1, mod++)
          if (mask & 1)
            printf("%s", *mod);
        putchar ('\n');
      }
    }

    void window::show()
    {
      xcb_map_window(native_handle->connection, native_handle->id);
      xcb_flush(native_handle->connection);
    }

    void window::hide()
    {
      xcb_unmap_window(native_handle->connection, native_handle->id);
      xcb_flush(native_handle->connection);
    }

    void window::close()
    {
      core::debug_print("window::close called.\n");
      xcb_unmap_window(native_handle->connection, native_handle->id);
      xcb_destroy_window(native_handle->connection, native_handle->id);
      xcb_flush(native_handle->connection);
      window::windows().erase(std::remove(window::windows().begin(), window::windows().end(), this), window::windows().end());
    }

    void window::choose_visual(implementation::platform_handle& handle)
    {
      const int default_screen = DefaultScreen(handle.display.get());

      if(flags.test(window_flag::opengl))
      {
        int attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        handle.visual_info.reset(glXChooseVisual(handle.display.get(), default_screen, attributes));
  
        if(!handle.visual_info)
        {
          core::debug_print("Call to glXChooseVisual failed.");
        }
      }
      else
      {
      }
    }

    void window::setup_window(implementation::platform_handle& handle)
    {
      Window root = DefaultRootWindow(handle.display.get());

      XSetWindowAttributes window_attributes;
      window_attributes.colormap = XCreateColormap(handle.display.get(), root, handle.visual_info->visual, AllocNone);
      window_attributes.event_mask =   ExposureMask      | StructureNotifyMask | PointerMotionMask
                                     | ButtonPressMask   | ButtonReleaseMask
                                     | EnterWindowMask   | LeaveWindowMask
                                     | KeyPressMask      | KeyReleaseMask;

      handle.id = static_cast<xcb_window_t>(XCreateWindow(handle.display.get(),
                                            root,
                                            static_cast<int>(position.x), static_cast<int>(position.y),
                                            static_cast<unsigned int>(size.width), static_cast<unsigned int>(size.width),
                                            0, // border width
                                            handle.visual_info->depth,
                                            InputOutput,
                                            handle.visual_info->visual,
                                            CWColormap | CWEventMask,
                                                          &window_attributes));

      // The magic incantation to receive and be able to check for the "window was closed" event
      //handle->wm_delete_window = XInternAtom(handle->display.get(), "WM_DELETE_WINDOW", False);
      //XSetWMProtocols(handle->display.get(), handle->id, &handle->wm_delete_window, 1);
      xcb_intern_atom_cookie_t cookie = xcb_intern_atom(handle.connection, 1, 12, "WM_PROTOCOLS");
      implementation::xcb_intern_atom_reply_ptr reply(xcb_intern_atom_reply(handle.connection, cookie, nullptr));

      xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(handle.connection, 0, 16, "WM_DELETE_WINDOW");
      handle.wm_delete_window.reset(xcb_intern_atom_reply(handle.connection, cookie2, nullptr));

      xcb_change_property(handle.connection, XCB_PROP_MODE_REPLACE, handle.id, reply->atom, 4, 32, 1, &handle.wm_delete_window->atom);
      // end magic

      xcb_flush(handle.connection);
    }

    void window::initialize_and_execute_platform_loop()
    {
      auto handle_ptr = implementation::create_handle();
      auto& handle = *handle_ptr;

      choose_visual(handle);

      setup_window(handle);

      setup_graphics_backend(handle);

      graphics_context = std::make_unique<graphics::skia_gl_context>();

      // Ensure calling thread is waiting for draw_condition_variable
      std::unique_lock<decltype(handle_mutex)> handle_lock(handle_mutex);
      native_handle = handle_ptr.release();
      handle_condition_variable.notify_one();

      // Continue calling thread before initiating event loop
      handle_lock.unlock();

      execute_event_loop();

      graphics_context.reset();
      delete native_handle;
      native_handle = nullptr;

      if(flags.test(window_flag::exit_on_close))
        core::application::instance().quit();
    }

    void window::setup_graphics_backend(implementation::platform_handle&handle)
    {
      handle.context = glXCreateContext(handle.display.get(), handle.visual_info.get(), nullptr, True);
      glXMakeCurrent(handle.display.get(), handle.id, handle.context);
    }

    void window::execute_event_loop()
    {
      bool running = true;

      while(running)
      {
        std::unique_ptr<xcb_generic_event_t, decltype(&free)> event_ptr(xcb_wait_for_event(native_handle->connection), &free);
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

            update_geometry();

            draw();

            swap_buffers();

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
            implementation::print_modifiers (button_press->state);

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
          case XCB_CLIENT_MESSAGE:
          {
            auto client_message = reinterpret_cast<xcb_client_message_event_t*>(event_ptr.get());

            if(client_message->data.data32[0] == native_handle->wm_delete_window->atom)
            {
              core::debug_print("WM_DELETE_WINDOW received.\n");
              close();
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

    void window::update_geometry()
    {
      // fetch true dimensions and position of visual window now because the ConfigureNotify event lies to us
      core::unique_free_ptr<xcb_get_geometry_reply_t> geom(xcb_get_geometry_reply(native_handle->connection,
                                                                                  xcb_get_geometry(native_handle->connection, native_handle->id),
                                                                                  nullptr));

      core::unique_free_ptr<xcb_query_tree_reply_t> tree(xcb_query_tree_reply(native_handle->connection,
                                                                              xcb_query_tree(native_handle->connection, native_handle->id),
                                                                              nullptr));

      xcb_translate_coordinates_cookie_t translateCookie = xcb_translate_coordinates(native_handle->connection,
                                                                                     native_handle->id,
                                                                                     tree->parent,
                                                                                     geom->x, geom->y);

      core::unique_free_ptr<xcb_translate_coordinates_reply_t> trans(xcb_translate_coordinates_reply(native_handle->connection,
                                                                                                     translateCookie,
                                                                                                     nullptr));

      size = { geom->width, geom->height };
      position = { trans->dst_x, trans->dst_y };
    }

    void window::swap_buffers()
    {
      if(flags.test(window_flag::opengl))
      {
        glXSwapBuffers(native_handle->display.get(), native_handle->id);
      }
      else
      {
        //TODO
      }
    }

    void window::set_title(const core::string& title)
    {
      XStoreName(native_handle->display.get(), native_handle->id, title.c_str());
    }

    core::string window::get_title() const
    {
      char* result = nullptr;
      XFetchName(native_handle->display.get(), native_handle->id, &result);
      if(!result)
        return {};

      core::string title(result);
      XFree(result);
      return title;
    }
  }
}
