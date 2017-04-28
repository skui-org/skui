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

#include <EGL/egl.h>

#include <xcb/xcb.h>

// For some reason, moving the code in this function to skui::gui::window::setup_window doesn't work.
void make_xcb_window(uint16_t width,
                     uint16_t height,
                     skui::gui::implementation::platform_handle& handle);

xcb_screen_t* screen_of_display(xcb_connection_t* connection,
                                int screen)
{
  xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(connection));
  do
  {
    if(screen == 0)
      return iter.data;

    --screen;
    xcb_screen_next(&iter);
  } while(iter.rem != 0);

  return nullptr;
}

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
      using xcb_intern_atom_reply_ptr = core::unique_free_ptr<xcb_intern_atom_reply_t>;

      class platform_handle
      {
      public:
        platform_handle()
          : connection(nullptr)
          , preferred_screen(nullptr)
          , wm_delete_window(nullptr)
          , visualid(0)
          , id(0)
          , egl_display(nullptr)
          , egl_context(nullptr)
          , egl_config(0)
          , egl_surface(nullptr)
        {}

        ~platform_handle()
        {
          if(egl_context)
          {
            eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            eglDestroyContext(egl_display, egl_context);
          }
          if(egl_surface)
            eglDestroySurface(egl_display, egl_surface);
          if(egl_display)
            eglTerminate(egl_display);
        }

        xcb_connection_t* connection;
        xcb_screen_t* preferred_screen;
        xcb_intern_atom_reply_ptr wm_delete_window;
        xcb_visualid_t visualid;
        xcb_window_t id;

        EGLDisplay egl_display;
        EGLContext egl_context;
        EGLConfig egl_config;
        EGLSurface egl_surface;
      };

      void platform_handle_deleter::operator()(platform_handle* handle) const
      {
        delete handle;
      }

      platform_handle_ptr create_handle()
      {
        platform_handle_ptr handle(new platform_handle);

        int preferred_screen;
        handle->connection = xcb_connect(nullptr, &preferred_screen);

        handle->preferred_screen = screen_of_display(handle->connection, preferred_screen);

        handle->egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(handle->egl_display == EGL_NO_DISPLAY)
          core::debug_print("Call to eglGetDisplay failed.\n");

        if(EGL_FALSE == eglInitialize(handle->egl_display, nullptr, nullptr))
          core::debug_print("Call to eglInitialize failed.\n");

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
  }
}

// definition lives here because it uses platform_handle.
void make_xcb_window(uint16_t width,
                     uint16_t height,
                     skui::gui::implementation::platform_handle& handle)
{
  handle.id = xcb_generate_id(handle.connection);

  static const uint32_t mask = XCB_CW_EVENT_MASK;
  static const uint32_t values[] = { XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_STRUCTURE_NOTIFY |
                                     XCB_EVENT_MASK_BUTTON_PRESS   | XCB_EVENT_MASK_BUTTON_RELEASE |
                                     XCB_EVENT_MASK_POINTER_MOTION |
                                     XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW |
                                     XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE };

  xcb_create_window(handle.connection,
                    XCB_COPY_FROM_PARENT,
                    handle.id,
                    handle.preferred_screen->root,
                    0, 0,
                    width, height,
                    10,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                    handle.visualid,
                    mask, values);
}

namespace skui
{
  namespace gui
  {
    const window_flags window::default_flags = window_flag::exit_on_close | window_flag::opengl;

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
      if(flags.test(window_flag::opengl))
      {
        if(EGL_FALSE == eglBindAPI(EGL_OPENGL_API))
          core::debug_print("Call to eglBindAPI failed.\n");

        static EGLint const attribute_list[]
        {
          EGL_RED_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_BLUE_SIZE, 8,
          EGL_ALPHA_SIZE, 8,
          EGL_NONE
        };

        EGLint num_config;
        if(EGL_FALSE == eglChooseConfig(handle.egl_display, attribute_list, &handle.egl_config, 1, &num_config))
          core::debug_print("Call to eglChooseConfig failed.\n");

        static const EGLint context_attributes[]
        {
          EGL_NONE
        };

        handle.egl_context = eglCreateContext(handle.egl_display, handle.egl_config, EGL_NO_CONTEXT, context_attributes);
        if(handle.egl_context == EGL_NO_CONTEXT)
          core::debug_print("Call to eglCreateContext failed.\n");

        //Request eglVisualID for native window
        EGLint egl_native_visualid;
        if(EGL_FALSE == eglGetConfigAttrib(handle.egl_display, handle.egl_config, EGL_NATIVE_VISUAL_ID, &egl_native_visualid))
          core::debug_print("Call to eglGetConfigAttrib failed\n");

        handle.visualid = static_cast<xcb_visualid_t>(egl_native_visualid);
      }
      else
      {
      }
    }

    void window::setup_window(implementation::platform_handle& handle)
    {
      make_xcb_window(static_cast<uint16_t>(size.width),
                      static_cast<uint16_t>(size.height),
                      handle);

      // The magic incantation to receive and be able to check for the "window was closed" event
      xcb_intern_atom_cookie_t cookie = xcb_intern_atom(handle.connection, 1, 12, "WM_PROTOCOLS");
      implementation::xcb_intern_atom_reply_ptr reply(xcb_intern_atom_reply(handle.connection, cookie, nullptr));

      xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(handle.connection, 0, 16, "WM_DELETE_WINDOW");
      handle.wm_delete_window.reset(xcb_intern_atom_reply(handle.connection, cookie2, nullptr));

      xcb_change_property(handle.connection, XCB_PROP_MODE_REPLACE, handle.id, reply->atom, 4, 32, 1, &handle.wm_delete_window->atom);
      // end magic

      xcb_flush(handle.connection);
    }

    void window::setup_graphics_backend(implementation::platform_handle& handle)
    {
      if(flags.test(window_flag::opengl))
      {
        handle.egl_surface = eglCreateWindowSurface(native_handle->egl_display,
                                           native_handle->egl_config,
                                           native_handle->id,
                                           nullptr);

        eglMakeCurrent(handle.egl_display, handle.egl_surface, handle.egl_surface, handle.egl_context);
      }
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

            repaint();

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
        eglSwapBuffers(native_handle->egl_display, native_handle->egl_surface);
      }
      else
      {
        //TODO
      }
    }

    void window::set_title(const core::string& title)
    {
      xcb_change_property(native_handle->connection,
                          XCB_PROP_MODE_REPLACE,
                          native_handle->id,
                          XCB_ATOM_WM_NAME,
                          XCB_ATOM_STRING,
                          8,
                          static_cast<std::uint32_t>(title.size()),
                          title.c_str());
      xcb_flush(native_handle->connection);
    }

    core::string window::get_title() const
    {
      xcb_get_property_cookie_t cookie = xcb_get_property(native_handle->connection,
                                                          0,
                                                          native_handle->id,
                                                          XCB_ATOM_WM_NAME,
                                                          XCB_ATOM_STRING,
                                                          0,
                                                          0);

      core::unique_free_ptr<xcb_get_property_reply_t> reply(
            xcb_get_property_reply(native_handle->connection,
                                   cookie,
                                   nullptr));

      if(reply)
      {
        int length = xcb_get_property_value_length(reply.get());
        if(length > 0)
        {
          const char* result = static_cast<char*>(xcb_get_property_value(reply.get()));
          return core::string(result, result + length);
        }
      }
      return "";
    }
  }
}
