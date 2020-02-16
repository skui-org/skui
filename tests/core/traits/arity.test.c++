/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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

#include "core/traits/arity.h++"

namespace
{
  [[maybe_unused]] void f() {}
  [[maybe_unused]] void g(int) {}
  //void h(...) {}

  [[maybe_unused]] const auto l = []{};
  [[maybe_unused]] const auto l_int = [](int){};

  struct mock
  {
    [[maybe_unused]] void f();
    [[maybe_unused]] void g(int);
  };
}

int main()
{
  using skui::core::arity_v;

  static_assert(arity_v<decltype(&f)> == 0, "arity of function without arguments is zero.");
  static_assert(arity_v<decltype(&g)> == 1, "arity of function with one argument is one.");
  //static_assert(arity_v<decltype(&h)> == 0, "arity of function with variadic arguments is ????.");

  static_assert(arity_v<decltype(l)> == 0, "arity of lambda without arguments is zero.");
  static_assert(arity_v<decltype(l_int)> == 1, "arity of lambda with one arguments is one.");

  static_assert(arity_v<decltype(&mock::f)> == 0, "arity of member function without arguments is zero.");
  static_assert(arity_v<decltype(&mock::g)> == 1, "arity of member function with one argument is one.");
}
