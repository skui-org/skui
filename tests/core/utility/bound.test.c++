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

#include "test.h++"

#include <core/utility/bound.h++>

namespace
{
  void test_bound_int()
  {
    static_assert(skui::core::bound<int>{}(-1,0,2) == 0, "bound moves smaller value to lower bound");
    static_assert(skui::core::bound<int>{}(0,0,2) == 0, "bound leaves lower bound as lower bound");
    static_assert(skui::core::bound<int>{}(1,0,2) == 1, "bound leaves value within bounds the same");
    static_assert(skui::core::bound<int>{}(2,0,2) == 2, "bound leaves upper bound as upper bound");
    static_assert(skui::core::bound<int>{}(3,0,2) == 2, "bound moves larger value to upper bound");
  }
}

int main()
{
  test_bound_int();

  return skui::test::exit_code;
}
