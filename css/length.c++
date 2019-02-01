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

#include "css/length.h++"

#include <iostream>

namespace skui::css
{
  std::ostream& operator<<(std::ostream& os, const unit unit)
  {
    switch(unit)
    {
      case unit::mm:
        return os << "mm";
      case unit::cm:
        return os << "cm";
      case unit::in:
        return os << "in";
      case unit::px:
        return os << "px";
      case unit::pt:
        return os << "pt";
      case unit::pc:
        return os << "pc";
      case unit::em:
        return os << "em";
      case unit::ex:
        return os << "ex";
      case unit::ch:
        return os << "ch";
      case unit::rem:
        return os << "rem";
      case unit::vw:
        return os << "vw";
      case unit::vh:
        return os << "vh";
      case unit::vmin:
        return os << "vmin";
      case unit::vmax:
        return os << "vmax";
      case unit::percentage:
        return os << "%";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const length& length)
  {
      return os << length.value << ' ' << length.unit;
  }
}
