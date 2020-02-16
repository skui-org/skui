/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2020 Ruben Van Boxem
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

#ifndef SKUI_CSS_POSITION_H
#define SKUI_CSS_POSITION_H

/*
 * css::position
 * Absolute position in pixels.
 * Relative position in percentage representing the size of the element.
 * Offset from relative
 */

#include "css/length.h++"

#include <iosfwd>
#include <optional>
#include <variant>

namespace skui::css
{
  struct length_with_offset
  {
    length value;
    length offset;
  };

  struct position
  {
    length_with_offset x;
    length_with_offset y;
  };

  static constexpr position top_left = {{{0, unit::percentage}, {}},
                                        {{0, unit::percentage}, {}}};
  static constexpr position top_center = {{{50, unit::percentage}, {}},
                                          {{0, unit::percentage}, {}}};
  static constexpr position top_right = {{{100, unit::percentage}, {}},
                                         {{0, unit::percentage}, {}}};
  static constexpr position center_left = {{{0, unit::percentage}, {}},
                                           {{50, unit::percentage}, {}}};
  static constexpr position center_center = {{{50, unit::percentage}, {}},
                                             {{50, unit::percentage}, {}}};
  static constexpr position center_right = {{{100, unit::percentage}, {}},
                                            {{50, unit::percentage}, {}}};
  static constexpr position bottom_left = {{{0, unit::percentage}, {}},
                                           {{100, unit::percentage}, {}}};
  static constexpr position bottom_center = {{{50, unit::percentage}, {}},
                                             {{100, unit::percentage}, {}}};
  static constexpr position bottom_right = {{{100, unit::percentage}, {}},
                                            {{100, unit::percentage}, {}}};

  static constexpr position left = center_left;
  static constexpr position right = center_right;
  static constexpr position center = center_center;
  static constexpr position top = top_center;
  static constexpr position bottom = bottom_center;

  constexpr bool operator==(const length_with_offset& lhs,
                            const length_with_offset& rhs)
  {
    return lhs.value == rhs.value
        && lhs.offset == rhs.offset;
  }

  constexpr bool operator==(const position& lhs,
                            const position& rhs)
  {
    return lhs.x == rhs.x
        && lhs.y == rhs.y;
  }
}

#endif
