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

namespace
{
  using skui::test::check;
  void test_boundedness()
  {
    skui::core::bounded_property<int> property(0, 0, 1);

    bool slot_called = false;
    const auto slot = [&slot_called](int) { slot_called = true; };
    property.value_changed.connect(slot);

    property = 2;
    check(property == 1, "Assigning out of bounds value does not emit changed signal.");
    check(slot_called, "Assigning out of bounds value does not emit changed signal.");
  }
}

int main()
{
  skui::test::run_all_property_tests<skui::core::bounded_property<int>>();

  test_boundedness();

  return skui::test::exit_code;
}
