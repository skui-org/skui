/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#ifndef SKUI_CSS_PROPERTY_BORDER_H
#define SKUI_CSS_PROPERTY_BORDER_H

#include "css/color.h++"
#include "css/length.h++"

#include <optional>
#include <variant>

namespace skui::css
{
  enum class border_width_enum
  {
    medium,
    thin,
    thick
  };

  enum class border_style
  {
    none,
    hidden,
    dotted,
    dashed,
    solid,
    double_,
    groove,
    ridge,
    inset,
    outset
  };

  using border_width = std::variant<border_width_enum, length>;

  struct border
  {
    struct side
    {
      border_width width{};
      border_style style{};
      css::color color{};
    };

    struct horizontal_side : side
    {
      length left_radius{};
      length right_radius{};
    };

    struct vertical_side : side
    {
      length top_radius{};
      length bottom_radius{};
    };

    horizontal_side top{};
    horizontal_side bottom{};
    vertical_side left{};
    vertical_side right{};
  };
}

#endif
