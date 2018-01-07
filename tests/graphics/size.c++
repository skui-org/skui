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

#include <graphics/size.h++>

namespace
{
  using skui::test::check;

  void test_constructor()
  {
      skui::graphics::size2D<int> size{1,2};

      check(size.width == 1, "size constructor sets width correctly.");
      check(size.height == 2, "size constructor sets height correctly.");
  }

  void test_equality_operators()
  {
    skui::graphics::size2D<int> size{1,2};

    check(  size == skui::graphics::size2D<int>{1,2},  "operator== returns true for same size");
    check(!(size == skui::graphics::size2D<int>{2,2}), "operator== returns false for different width");
    check(!(size == skui::graphics::size2D<int>{1,1}), "operator== returns false for different height");
    check(!(size == skui::graphics::size2D<int>{2,1}), "operator== returns false for different size");

    check(!(size != skui::graphics::size2D<int>{1,2}), "operator!= returns false for same size");
    check(  size != skui::graphics::size2D<int>{2,2},  "operator!= returns true for different width");
    check(  size != skui::graphics::size2D<int>{1,1},  "operator!= returns true for different height");
    check(  size != skui::graphics::size2D<int>{2,1},  "operator!= returns true for different size");
  }
}

int main()
{
  test_constructor();
  test_equality_operators();

  return skui::test::exit_code;
}
