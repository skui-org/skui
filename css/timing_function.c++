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

#include "css/timing_function.h++"

#include <iostream>

namespace skui::css
{
  std::ostream& operator<<(std::ostream& os, const steps& steps)
  {
    return os << "steps(" << steps.intervals << ", " << steps.change << ')';
  }

  std::ostream& operator<<(std::ostream& os, const cubic_bezier& cubic_bezier)
  {
    return os << "cubic-bezier(" << cubic_bezier.x1 << ", " << cubic_bezier.y1 << ", "
                                 << cubic_bezier.x2 << ", " << cubic_bezier.y2 << ')';
  }

  std::ostream& operator<<(std::ostream& os, const timing_function& timing_function)
  {
    std::visit([&os](const auto& value) { os << value; }, timing_function);
    return os;
  }
}
