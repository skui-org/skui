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

#include <gui/make_element.h++>

namespace
{
  using skui::test::check;
  using skui::test::require;

  struct mock_element : public skui::gui::element
  {
  public:
    mock_element(int value) : value(value) {}

    void draw(skui::graphics::canvas&,
              const skui::graphics::scalar_position&) const override
    {}
    skui::graphics::scalar_size implicit_size() const override
    {
      return {};
    }

    int value;
  };

  void test_make_element()
  {
    const auto element = skui::gui::make<mock_element>(1);

    check(element->value == 1, "Arguments passed through make_element to actual constructor");

    const auto elements = skui::gui::make_element_ptrs(skui::gui::make<mock_element>(1),
                                                       skui::gui::make<mock_element>(2));

    require(elements.size() == 2, "Correct number of elements in result");
    mock_element* pointer = dynamic_cast<mock_element*>(elements[0].get());
    require(pointer, "First object properly stored");
    check(pointer->value == 1, "First element has correct value");

    pointer = dynamic_cast<mock_element*>(elements[1].get());
    require(pointer, "Second object properly stored");
    check(pointer->value == 2, "Second element has the correct value");
  }
}

int main()
{
  test_make_element();

  return skui::test::exit_code;
}
