/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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
 * native_window::xlib
 * Native Window implementation for XLib.
 */

#ifndef SKUI_GUI_NATIVE_WINDOW_XLIB_H
#define SKUI_GUI_NATIVE_WINDOW_XLIB_H

#include "gui/native_window/xcb.h++"

#include <memory>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>

namespace skui::gui::native_window
{
  // helper struct to ensure correct base class constructor can be called
  struct xlib_data
  {
    xlib_data(Display* display) : display{display} {}
    struct display_deleter
    {
      void operator()(Display* display) const { XCloseDisplay(display); }
    };
    std::unique_ptr<Display, display_deleter> display;
  };

  class xlib : public xlib_data
             , public xcb
  {
  public:
    xlib(const window_flags& flags);
    ~xlib() override;

    void create(const graphics::pixel_position& initial_position,
                const graphics::pixel_size& initial_size) override;

    XVisualInfo* get_xvisualinfo() const;
    void handle_dri2_events(xcb_generic_event_t& event) const;
  };
}

#endif
