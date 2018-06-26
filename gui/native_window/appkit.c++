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

#include "gui/native_window/appkit.h++"

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      appkit::appkit(std::unique_ptr<native_visual::base> native_visual)
        : base{std::move(native_visual)}
      {}

      appkit::~appkit() = default;

      void appkit::create(const graphics::pixel_position&,
                          const graphics::pixel_size&)
      {}

      void appkit::show()
      {}

      void appkit::hide()
      {}

      void appkit::close()
      {}

      core::string appkit::get_title() const
      {
          return {};
      }

      void appkit::set_title(const core::string&)
      {}

      std::pair<graphics::pixel_position, graphics::pixel_size> appkit::get_current_geometry() const
      {
        return {};
      }
    }
  }
}
