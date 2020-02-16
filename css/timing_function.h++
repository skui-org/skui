/**
 * The MIT License (MIT)
 *
 * Copyright © 2019-2020 Ruben Van Boxem
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

#ifndef SKUI_CSS_TIMING_FUNCTION_H
#define SKUI_CSS_TIMING_FUNCTION_H

#include <iosfwd>
#include <variant>

namespace skui::css
{
  struct steps
  {
    unsigned int intervals;
    enum
    {
      start,
      end
    } change{end};
  };

  struct cubic_bezier
  {
    // defaults correspond to "ease"
    float x1{.25f};
    float y1{0.1f};
    float x2{.25f};
    float y2{1};
  };

  using timing_function = std::variant<cubic_bezier,
                                       steps>;

  constexpr auto ease = cubic_bezier{.25f, .1f, .25f, 1};
  constexpr auto linear = cubic_bezier{0, 0, 1, 1};
  constexpr auto ease_in = cubic_bezier{.42f, 0, 1, 1};
  constexpr auto ease_out = cubic_bezier{0, 0, .58f, 1};
  constexpr auto ease_in_out = cubic_bezier{.42f, 0, .58f, 1};
  constexpr auto step_start = steps{1, steps::start};
  constexpr auto step_end = steps{1, steps::end};

  constexpr bool operator==(const steps& lhs, const steps& rhs)
  {
    return lhs.intervals == rhs.intervals
        && lhs.change == rhs.change;
  }
  constexpr bool operator==(const cubic_bezier& lhs, const cubic_bezier& rhs)
  {
    return lhs.x1 == rhs.x1
        && lhs.y1 == rhs.y1
        && lhs.x2 == rhs.x2
        && lhs.y2 == rhs.y2;
  }
  std::ostream& operator<<(std::ostream& os, const steps& steps);
  std::ostream& operator<<(std::ostream& os, const cubic_bezier& cubic_bezier);
  std::ostream& operator<<(std::ostream& os, const timing_function& timing_function);
}

#endif
