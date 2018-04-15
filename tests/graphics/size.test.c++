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
 * OUT OF OR IN CONnECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "test.h++"

#include "graphics/composite_value_tests.h++"

#include <graphics/size.h++>

namespace
{
  using skui::test::check;

  using int_size = skui::graphics::size2D<int>;

  void test_constructor()
  {
    int_size size{1, 2};

    check(size.width == 1, "constructor sets width correctly.");
    check(size.height == 2, "constructor sets height correctly.");
  }

  void test_equality()
  {
    int_size one_one{1, 1};
    int_size one_two{1, 2};
    int_size two_one{2, 1};
    int_size two_two{2, 2};

    check(  one_one == one_one, "== returns true for same sizes");
    check(!(one_two == one_one), "== returns false when height differs");
    check(!(two_one == one_one), "== returns false when width differs");
    check(!(one_one == two_two), "== returns false for different sizes");

    check(!(one_one != one_one), "!= returns false for same sizes");
    check(  one_two != one_one, "!= returns true for different height");
    check(  two_one != one_one, "!= returns true for different width");
    check(  one_one != two_two, "!= returns true for different sizes");
  }

  void test_addition_subtraction()
  {
    int_size one{0, 1};
    int_size two{2, 3};

    check(one + two == int_size{2, 4}, "+ adds sizes");
    check(two - one == int_size{2, 2}, "- subtracts sizes");

    auto three = two;

    three-=one;
    check(three == int_size{2, 2}, "-= subtracts sizes");

    three += one;
    check(three == int_size{2, 3}, "+= adds sizes");
  }

  void test_multiplication_division()
  {
    int_size two{2, 4};

    check(two * 2 == int_size{4, 8}, "* multiplies size");
    check(two / 2 == int_size{1, 2}, "/ divides size");

    two *= 2;
    check(two == int_size{4, 8}, "*= multiplies size");

    two /= 2;
    check(two == int_size{2, 4}, "/= divides size");
  }
}

int main()
{
  test_constructor();
  test_equality();
  test_addition_subtraction();
  test_multiplication_division();

  skui::test::run_all_composite_value_tests<skui::graphics::size2D<int>>();

  return skui::test::exit_code;
}
