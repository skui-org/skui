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

#include "gui/mock_canvas.h++"
#include "gui/mock_element.h++"

#include <gui/layout/row.h++>

namespace
{
  using skui::test::check_close;
  using skui::test::epsilon;
  using skui::test::mock_canvas;
  using skui::test::mock_element;

  void test_implicit_size()
  {
    skui::gui::row row(std::make_unique<mock_element>(10),
                       std::make_unique<mock_element>(0),
                       std::make_unique<mock_element>(5));
    check_close(row.implicit_size(mock_canvas{}),
                {15, 10},
                epsilon<skui::graphics::scalar_size>, "implicit_size returns correct value");
    row.spacing = 3;
    check_close(row.implicit_size(mock_canvas{}),
                {21, 10},
                epsilon<skui::graphics::scalar_size>, "implicit_size takes spacing into account correctly");
  }
}

int main()
{
  test_implicit_size();

  return skui::test::exit_code;
}
