/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
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

#ifndef SKUI_CSS_COLOR_STOP_H
#define SKUI_CSS_COLOR_STOP_H

#include "css/angle.h++"
#include "css/color.h++"
#include "css/length.h++"

#include <optional>

namespace skui::css
{
  template<typename StopType = css::length>
  struct color_stop
  {
    css::color color;
    std::optional<StopType> stop;
  };

  using linear_color_stop = color_stop<length>;
  using angular_color_stop = color_stop<angle>;

  template<typename StopType>
  constexpr bool operator==(const color_stop<StopType>& lhs,
                            const color_stop<StopType>& rhs)
  {
      return lhs.color == rhs.color
          && lhs.stop == rhs.stop;
  }
}

#endif
