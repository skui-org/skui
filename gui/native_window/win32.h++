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

/*
 * native_window::win32
 * Native Window implementation for Win32.
 */

#ifndef SKUI_GUI_NATIVE_WINDOW_WIN32_H
#define SKUI_GUI_NATIVE_WINDOW_WIN32_H

#include "gui/native_window.h++"

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      class win32 : public base
      {
      public:
        win32(std::unique_ptr<native_visual::base>&& native_visual);
        ~win32() override;

        void create(const graphics::pixel_position& initial_position,
                    const graphics::pixel_size& initial_size) override;
        void show() override;
        void hide() override;
        void close() override;
        core::string get_title() const override;
        void set_title(const core::string& title) override;
        void get_current_geometry(graphics::pixel_position& position,
                                  graphics::pixel_size& size) const override;

        HWND get_hwnd() const;

      private:
        HWND window;
      };
    }
  }
}

#endif
