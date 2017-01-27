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

#include "window.h++"

#include <core/application.h++>
#include <core/debug.h++>

#include <GrGLInterface.h>
#include <GrContext.h>

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
      using xdisplay_ptr = std::unique_ptr<Display, decltype(&XCloseDisplay)>;
      using xvisualinfo_ptr = std::unique_ptr<XVisualInfo, decltype(&XFree)>;
      using xcb_intern_atom_reply_ptr = std::unique_ptr<xcb_intern_atom_reply_t, decltype(&free)>;

      class platform_handle
      {
      public:
        platform_handle()
          : display(nullptr, &XCloseDisplay)
          , connection(nullptr)
          , id(0)
          , wm_delete_window(nullptr, &free)
          , visual_info(nullptr, &XFree)
          , context(nullptr)
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

    window::~window()
    {
      core::debug_print("Destroying window.\n");
      if(native_handle)
      {
        close();
      }
      thread.join();
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

    void window::initialize_and_execute_platform_loop()
    {
      auto handle = std::make_unique<implementation::platform_handle>();

      // Open Display connection for GLX
      handle->display.reset(XOpenDisplay(nullptr));
      if(!handle->display)
      {
        core::debug_print("Call to XOpenDisplay failed.");
        return;
      }

      // Handover to XCB for event handling
      handle->connection = XGetXCBConnection(handle->display.get());
      XSetEventQueueOwner(handle->display.get(), XCBOwnsEventQueue);

      Window root = DefaultRootWindow(handle->display.get());

      const int default_screen = DefaultScreen(handle->display.get());
      //xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(handle->connection)).data;

      int attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
      handle->visual_info.reset(glXChooseVisual(handle->display.get(), default_screen, attributes));

      if(!handle->visual_info)
      {
        core::debug_print("Call to glXChooseVisual failed.");
        return;
      }
/* BROKEN
      handle->id = xcb_generate_id(handle->connection);

      xcb_colormap_t colormap = xcb_generate_id(handle->connection);
      xcb_create_colormap(handle->connection,
                          XCB_COLORMAP_ALLOC_NONE,
                          colormap,
                          screen->root,
                          screen->root_visual);
      std::uint32_t cw_mask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
      std::uint32_t cw_values[]{  colormap,
                                  XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_STRUCTURE_NOTIFY
                                | XCB_EVENT_MASK_BUTTON_PRESS   | XCB_EVENT_MASK_BUTTON_RELEASE
                                | XCB_EVENT_MASK_POINTER_MOTION
                                | XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW
                                | XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE };

      xcb_create_window(handle->connection,
                        static_cast<std::uint8_t>(handle->visual_info->depth), // depth
                        handle->id,
                        screen->root, // parent window
                        static_cast<std::int16_t>(position.x), static_cast<std::int16_t>(position.y),
                        static_cast<std::uint16_t>(size.width), static_cast<std::uint16_t>(size.width),
                        0, // border width
                        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
                        static_cast<xcb_visualid_t>(handle->visual_info->visualid), // visual
                        cw_mask,
                        cw_values);
*/
      XSetWindowAttributes window_attributes;
      window_attributes.colormap = XCreateColormap(handle->display.get(), root, handle->visual_info->visual, AllocNone);
      window_attributes.event_mask =   ExposureMask      | StructureNotifyMask
                                     | ButtonPressMask   | ButtonReleaseMask
                                     | PointerMotionMask
                                     | EnterWindowMask   | LeaveWindowMask
                                     | KeyPressMask      | KeyReleaseMask;

      handle->id = static_cast<xcb_window_t>(XCreateWindow(handle->display.get(),
                                            root,
                                 static_cast<int>(position.x), static_cast<int>(position.y),
                                 static_cast<unsigned int>(size.width), static_cast<unsigned int>(size.width),
                                               0, // border width
                                 handle->visual_info->depth,
                                 InputOutput,
                                 handle->visual_info->visual,
                                 CWColormap | CWEventMask,
                                 &window_attributes));

      //XMapWindow(handle->display.get(), handle->id);
      core::string name = core::application::instance().name;
      XStoreName(handle->display.get(), handle->id, name.c_str());

      //xcb_map_window(handle->connection, handle->id);

      GLXContext glx_context = glXCreateContext(handle->display.get(), handle->visual_info.get(), nullptr, True);
      glXMakeCurrent(handle->display.get(), handle->id, glx_context);

      glEnable(GL_DEPTH_TEST);

      // The magic incantation to receive and be able to check for the "window was closed" event
      //handle->wm_delete_window = XInternAtom(handle->display.get(), "WM_DELETE_WINDOW", False);
      //XSetWMProtocols(handle->display.get(), handle->id, &handle->wm_delete_window, 1);
      xcb_intern_atom_cookie_t cookie = xcb_intern_atom(handle->connection, 1, 12, "WM_PROTOCOLS");
      implementation::xcb_intern_atom_reply_ptr reply(xcb_intern_atom_reply(handle->connection, cookie, nullptr), &free);

      xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(handle->connection, 0, 16, "WM_DELETE_WINDOW");
      handle->wm_delete_window.reset(xcb_intern_atom_reply(handle->connection, cookie2, nullptr));

      xcb_change_property(handle->connection, XCB_PROP_MODE_REPLACE, handle->id, reply->atom, 4, 32, 1, &handle->wm_delete_window->atom);
      // end magic

      xcb_flush(handle->connection);

      // Ensure calling thread is waiting for draw_condition_variable
      std::unique_lock<decltype(handle_mutex)> handle_lock(handle_mutex);
      native_handle = handle.release();
      handle_condition_variable.notify_one();

      // Skia setup
      sk_sp<const GrGLInterface> interface(GrGLCreateNativeInterface());
      sk_sp<const GrGLInterface> backend_context(GrGLInterfaceRemoveNVPR(interface.get()));
      sk_sp<GrContext> context(GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)backend_context.get()));
      //GrPixelConfig pixel_config = context->caps()->srgbSupport() /*&& fDisplayParams.fColorSpace */&&
      //               (fColorBits != 30) ? kSRGBA_8888_GrPixelConfig : kRGBA_8888_GrPixelConfig;

      // Continue calling thread before initiating event loop
      handle_lock.unlock();

      // Event loop
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
          case XCB_CONFIGURE_NOTIFY:
          {
            auto configure = reinterpret_cast<xcb_configure_notify_event_t*>(event_ptr.get());

            core::debug_print("Window ", configure->window, " configured. ");
            size = { configure->width, configure->height };
            position = { configure->x, configure->y };

            core::debug_print("New window geometry: (", position.x, ", ", position.y, "): ", size.width, "x", size.height, ".\n");
            break;
          }
          case XCB_EXPOSE:
          {
            auto expose = reinterpret_cast<xcb_expose_event_t*>(event_ptr.get());

            core::debug_print("Window ", expose->window, " exposed. "
                              "Region to be redrawn at location (", expose->x, ", ", expose->y, "), with dimension (", expose->width, ", ", expose->height, ").\n");

            core::debug_print("render thread: ", std::this_thread::get_id());
            glViewport(0, 0, static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height));
            draw();
            glXSwapBuffers(native_handle->display.get(), native_handle->id);
            break;
          }
          case XCB_UNMAP_NOTIFY:
          {
            auto unmap = reinterpret_cast<xcb_unmap_notify_event_t*>(event_ptr.get());

            core::debug_print("Window ", unmap->window, " unmapped.\n");
          }
          case XCB_BUTTON_PRESS:
          {
            auto button_press = reinterpret_cast<xcb_button_press_event_t*>(event_ptr.get());
            implementation::print_modifiers (button_press->state);

            switch (button_press->detail)
            {
              case 4:
                core::debug_print("Wheel Button up in window ", button_press->event, ", at coordinates (", button_press->event_x, ",", button_press->event_y, ").\n");
                break;
              case 5:
                core::debug_print("Wheel Button down in window ", button_press->event, ", at coordinates (", button_press->event_x, ",", button_press->event_y, ").\n");
                break;
              default:
                core::debug_print("Button ", button_press->detail, " pressed in window ", button_press->event, ", at coordinates (", button_press->event_x, ",", button_press->event, ").\n");
                break;
            }
            break;
          }
          case XCB_BUTTON_RELEASE:
          {
            auto button_release = reinterpret_cast<xcb_button_release_event_t*>(event_ptr.get());
            implementation::print_modifiers(button_release->state);

            core::debug_print("Button ", button_release->detail, " released in window ", button_release->event, ", at coordinates (", button_release->event_x, ",", button_release->event_y, ").\n");
            break;
          }
          case XCB_MOTION_NOTIFY:
          {
            auto motion = reinterpret_cast<xcb_motion_notify_event_t*>(event_ptr.get());

            core::debug_print("Mouse moved in window ", motion->event, ", at coordinates (", motion->event_x, ",", motion->event_y, ").\n");
            break;
          }
          case XCB_ENTER_NOTIFY:
          {
            auto enter = reinterpret_cast<xcb_enter_notify_event_t*>(event_ptr.get());

            core::debug_print("Mouse entered window ", enter->event, ", at coordinates (", enter->event_x, ",", enter->event_y, ").\n");
            break;
          }
          case XCB_LEAVE_NOTIFY:
          {
            auto leave = reinterpret_cast<xcb_leave_notify_event_t*>(event_ptr.get());

            core::debug_print("Mouse left window ", leave->event, ", at coordinates (", leave->event_x, ",", leave->event_y, ").\n");
            break;
          }
          case XCB_KEY_PRESS:
          {
            auto key_press = reinterpret_cast<xcb_key_press_event_t*>(event_ptr.get());
            implementation::print_modifiers(key_press->state);

            core::debug_print("Key pressed in window ", key_press->event, ".\n");
            break;
          }
          case XCB_KEY_RELEASE:
          {
            auto key_release = reinterpret_cast<xcb_key_release_event_t*>(event_ptr.get());
            implementation::print_modifiers(key_release->state);

            core::debug_print("Key released in window ", key_release->event, ".\n");
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
            core::debug_print("Destroy notify.\n");
            running = false;
            delete native_handle;
            native_handle = nullptr;
            break;
          }
          default:
            core::debug_print("Unknown event: ", event_ptr->response_type & ~0x80, ".\n");
            break;
        }
      }
      core::debug_print("Ending X event loop.\n");
      if(flags.test(window_flags::exit_on_close))
      {
        core::debug_print("Exiting application after window close.\n");
        core::application::instance().quit();
      }
    }
  }
}
