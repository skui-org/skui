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

#include "gui/native_window/xlib.h++"
#include "gui/window_flags.h++"

#include "gui/native_visual/glx.h++"
#include "gui/native_visual/xcb.h++"

#include <core/debug.h++>

#include <X11/Xlib-xcb.h>

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      namespace
      {
        std::unique_ptr<native_visual::base> create_native_visual(Display* display,
                                                                  const window_flags& flags)
        {
          if(flags.test(window_flag::opengl))
            return std::make_unique<native_visual::glx>(display);
          else
          {
            xcb_connection_t* connection = XGetXCBConnection(display);
            core::debug_print("XCB connection: ", connection, '\n');

            xcb_screen_t* screen = (xcb_setup_roots_iterator(xcb_get_setup(connection))).data;

            return std::make_unique<native_visual::xcb>(connection, screen);
          }
        }
      }
      xlib::xlib(const window_flags& flags)
        : xlib_data{XOpenDisplay(nullptr)}
        , xcb(create_native_visual(display.get(), flags),
              XGetXCBConnection(display.get()))
      {
        XSetEventQueueOwner(display.get(), XCBOwnsEventQueue);
      }

      xlib::~xlib() = default;

      void xlib::create(const graphics::pixel_position& initial_position,
                        const graphics::pixel_size& initial_size)
      {
        Window root = DefaultRootWindow(display.get());

        XVisualInfo* xvisualinfo = get_xvisualinfo();

        XSetWindowAttributes window_attributes;
        window_attributes.colormap = XCreateColormap(display.get(), root, xvisualinfo->visual, AllocNone);
        window_attributes.event_mask =   ExposureMask      | StructureNotifyMask | PointerMotionMask
                                       | ButtonPressMask   | ButtonReleaseMask
                                       | EnterWindowMask   | LeaveWindowMask
                                       | KeyPressMask      | KeyReleaseMask;

        window = static_cast<xcb_window_t>(
                   XCreateWindow(display.get(),
                                 root,
                                 static_cast<int>(initial_position.x), static_cast<int>(initial_position.y),
                                 static_cast<unsigned int>(initial_size.width), static_cast<unsigned int>(initial_size.width),
                                 0, // border width
                                 xvisualinfo->depth,
                                 InputOutput,
                                 xvisualinfo->visual,
                                 CWColormap | CWEventMask,
                                 &window_attributes));

        native_visual->create_surface(window);
      }

      XVisualInfo* xlib::get_xvisualinfo() const
      {
        auto glx_native_visual = dynamic_cast<native_visual::glx*>(native_visual.get());
        if(glx_native_visual)
          return glx_native_visual->get_xvisualinfo();
        else
        {
          core::debug_print("native_window::xlib currently only handles native_visual::glx.");
          return nullptr;
        }
      }
    }
  }
}

