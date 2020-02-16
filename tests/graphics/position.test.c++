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
 * OUT OF OR IN CONnECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "test.h++"

#include "graphics/composite_value_tests.h++"

#include <graphics/position.h++>

namespace
{
  using skui::test::check;

  using int_position = skui::graphics::position2D<int>;

  void test_constructor()
  {
    int_position position{1,2};

    check(position.x == 1, "constructor sets width correctly.");
    check(position.y == 2, "constructor sets height correctly.");
  }

  void test_addition_subtraction()
  {
    int_position position{1,2};

    check((position + position) == int_position{2,4}, "operator+ does the right thing");
    check((position - position) == int_position{0,0}, "operator- does the right thing");

    position += {1,2};

    check(position.x == 2 && position.y == 4, "operator+= does the right thing");

    position -= {2,1};

    check(position.x == 0 && position.y == 3, "operator-= does the right thing");
  }
}

int main()
{
  test_constructor();
  test_addition_subtraction();

  skui::test::run_all_composite_value_tests<int_position>();

  return skui::test::exit_code;
}
