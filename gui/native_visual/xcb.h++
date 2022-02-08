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
 * native_visual::xcb
 * Native Visual implementation for XCB.
 */

#ifndef SKUI_GUI_NATIVE_VISUAL_XCB_H
#define SKUI_GUI_NATIVE_VISUAL_XCB_H

#include "gui/native_visual/raster.h++"

#include <vector>

#include <xcb/xcb.h>

namespace skui::gui::native_visual
{
  class xcb : public raster
  {
  public:
    xcb(xcb_connection_t* connection,
        xcb_screen_t* screen);
    ~xcb() override;

    void create_surface(std::uintptr_t window) override;
    void make_current() const override;
    void make_no_current() const override;
    void swap_buffers(const graphics::pixel_size& size) const override;

    xcb_visualid_t visualid() const;

  private:
    xcb_connection_t* connection;
    xcb_screen_t* screen;
    xcb_visualtype_t* visualtype;

    xcb_window_t window;
    xcb_gcontext_t gcontext;
  };
}

#endif
