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
 * native_window::xcb
 * Native Window implementation for XCB.
 */

#ifndef SKUI_GUI_NATIVE_WINDOW_XCB_H
#define SKUI_GUI_NATIVE_WINDOW_XCB_H

#include "gui/native_window.h++"

#include <core/utility.h++>

#include <memory>

#include <xcb/xcb.h>

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      class xcb : public base
      {
      public:
        xcb(std::unique_ptr<native_visual::base>&& native_visual);
        xcb(std::unique_ptr<native_visual::base>&& native_visual,
            xcb_connection_t* connection,
            int preferred_screen);
        ~xcb() override;

        void create(const graphics::pixel_position& position,
                    const graphics::pixel_size& size) override;
        void show() override final;
        void hide() override final;
        void close() override final;

        core::string get_title() const override final;
        void set_title(const core::string& title) override final;
        void get_current_geometry(graphics::pixel_position& position,
                                  graphics::pixel_size& size) override;

        xcb_connection_t* get_connection() const;
        xcb_window_t get_window() const;

      protected:
        xcb_window_t window;

      private:
        xcb_connection_t* connection;
        xcb_screen_t* preferred_screen;
      };
    }
  }
}

#endif
