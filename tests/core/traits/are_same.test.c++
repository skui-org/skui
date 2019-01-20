/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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

#include <core/traits/are_same.h++>

namespace
{
  struct incomplete;
  struct other_incomplete;
}

int main()
{
  using skui::core::are_same;

  static_assert(are_same<int, int, int>, "3 ints are the same type");
  static_assert(!are_same<int, int, int&>, "an int& is not the same as an int");
  static_assert(!are_same<int, char>, "an int and char are not the same type");
  static_assert(are_same<incomplete, incomplete>, "incomplete types are the same");
  static_assert(!are_same<incomplete, other_incomplete>, "two distinct incomplete types are not the same");

  return skui::test::exit_code;
}
