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

#include <core/overload.h++>

namespace
{
  using skui::core::overload;

  using skui::test::check;

  bool no_arguments{false};
  bool single_argument{false};
  bool two_arguments{false};
  bool default_argument{false};
  bool virtual_function{false};

  void f() { no_arguments = true; }
  void f(int) { single_argument = true; }
  void f(short, long) { two_arguments = true; }
  void f(char = '\0') { default_argument = true; }

  struct A
  {
    void f() { no_arguments = true; }
    void f(int) { single_argument = true; }
    void f(short, long) { two_arguments = true; }
    void f(char = '\0') { default_argument = true; }

    virtual void g() {};
  };

  struct B : A
  {
    void g() override { virtual_function = true; };
  };

  void test_free_function()
  {
    no_arguments = false;
    overload<>(&f)();
    check(no_arguments, "function with no arguments called.");

    single_argument = false;
    overload<int>(&f)(1);
    check(single_argument, "function with single argument called.");

    two_arguments = false;
    overload<short, long>(&f)(1, 2);
    check(two_arguments, "function with two arguments called.");

    default_argument = false;
    overload<char>(&f)('1');
    check(default_argument, "function with default argument called.");
  }

  void test_member_function()
  {
    A a;
    no_arguments = false;
    (a.*overload<>(&A::f))();
    check(no_arguments, "function with no arguments called.");

    single_argument = false;
    (a.*overload<int>(&A::f))(1);
    check(single_argument, "function with single argument called.");

    two_arguments = false;
    (a.*overload<short, long>(&A::f))(1, 2);
    check(two_arguments, "function with two arguments called.");

    default_argument = false;
    (a.*overload<char>(&A::f))('1');
    check(default_argument, "function with default argument called.");

    B b;
    virtual_function = false;
    (b.*overload<>(&A::g))();
    check(virtual_function, "virtual funtion called.");
  }
}

int main()
{
  test_free_function();
  test_member_function();

  return skui::test::exit_code;
}
