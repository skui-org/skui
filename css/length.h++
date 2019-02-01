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

#ifndef SKUI_CSS_LENGTH_H
#define SKUI_CSS_LENGTH_H

#include <iosfwd>

namespace skui::css
{
  enum class unit
  {
    // absolute
    cm, // centimeters
    mm, // millimeters
    in, // inches (1in = 96px = 2.54cm)
    px, // pixels (1px = 1/96th of 1in)
    pt, // points (1pt = 1/72 of 1in)
    pc, // picas (1pc = 12 pt)
    // relative
    em, // Relative to the font-size of the element (2em means 2 times the size of the current font)
    ex, // Relative to the x-height of the current font (rarely used)
    ch, // Relative to width of the "0" (zero)
    rem, // Relative to font-size of the root element
    vw, // Relative to 1% of the width of the viewport
    vh, // Relative to 1% of the height of the viewport
    vmin, // Relative to 1% of viewport's smaller dimension
    vmax, // Relative to 1% of viewport's larger dimension
    percentage, // Relative to the parent element
  };

  struct length
  {
    float value;

    css::unit unit;
  };

  std::ostream& operator<<(std::ostream& os, const css::unit unit);
  std::ostream& operator<<(std::ostream& os, const length& length);

  constexpr bool operator==(const length& left, const length& right)
  {
    return left.value == right.value && left.unit == right.unit;
  }
}

#endif
