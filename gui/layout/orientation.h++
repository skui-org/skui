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
 * layout::orientation
 * Describes the relative orientation of elements or an element's children.
 */

#ifndef SKUI_GUI_LAYOUT_ORIENTATION_H
#define SKUI_GUI_LAYOUT_ORIENTATION_H

#include <core/bitflag.h++>

namespace skui
{
  namespace gui
  {
    namespace layout
    {
      enum class orientation : std::uint8_t
      {
        horizontal = 1,
        vertical = 2,

        left_to_right = horizontal,
        right_to_left = 4 | horizontal,
        top_to_bottom = vertical,
        bottom_to_top = 8 | vertical,

        grid = 16
      };
    }
  }
  namespace core
  {
    template<>
    struct enum_is_bitflag<gui::layout::orientation> : std::true_type {};
  }
  namespace gui
  {
    namespace layout
    {
      using orientation_flags = core::bitflag<orientation>;
    }
    using namespace core::bitflag_operators;
  }
}

#endif
