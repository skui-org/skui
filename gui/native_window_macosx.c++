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

#include "gui/native_window.h++"

#include "gui/native_window/appkit.h++"

#include "gui/native_visual/coregraphics.h++"
#include "gui/native_visual/cgl.h++"

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      std::unique_ptr<base> create(const graphics::pixel_position& position,
                                   const graphics::pixel_size& size,
                                   const window_flags& flags)
      {
        std::unique_ptr<native_visual::base> visual;
        if(flags.test(window_flag::opengl))
          visual = std::make_unique<native_visual::cgl>();
        else
          visual = std::make_unique<native_visual::coregraphics>();

        std::unique_ptr<base> window = std::make_unique<appkit>(std::move(visual));

        window->create(position, size);

        return window;
      }
    }
  }
}

