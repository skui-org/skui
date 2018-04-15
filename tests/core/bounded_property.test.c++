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

#include "property_tests.h++"

#include "core/bounded_property.h++"

#include "gui/make_element.h++"

namespace
{
  using skui::test::check;

  void test_bounding()
  {
    skui::core::bounded_property<int> property(0, 0, 1);

    bool slot_called = false;
    const auto slot = [&slot_called](int) { slot_called = true; };
    property.value_changed.connect(slot);

    property = 2;
    check(property == 1, "Assigning out of bounds value does not emit changed signal.");
    check(slot_called, "Assigning out of bounds value does not emit changed signal.");
  }

  void test_initial_bounds()
  {
    skui::core::bounded_property<int> property;

    check(property.maximum == std::numeric_limits<int>::max(), "default maximum is largest value");
    check(property.minimum == std::numeric_limits<int>::lowest(), "default minimum is smallest value");
  }

  void test_minimum_maximum()
  {
    skui::core::bounded_property<int> property(2);

    property.minimum = 1;

    check(property == 2, "setting minimum below current value does not change value");

    property.maximum = 1;

    check(property == 1, "setting maximum below current value clamps value");
  }

  void test_fixed()
  {
    skui::core::bounded_property<int> property(0, 0, 0);
    check(property.fixed(), "property is fixed when minimum == maximum");
  }
}

int main()
{
  skui::test::run_all_property_tests<skui::core::bounded_property<int>>();

  test_bounding();
  test_initial_bounds();
  test_minimum_maximum();
  test_fixed();

  return skui::test::exit_code;
}
