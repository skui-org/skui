/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ruben Van Boxem
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

#include "core/property.h++"

namespace
{
  using skui::test::assert;

  void test_basic_operations()
  {
    skui::core::property<int> property;
    assert(property == 0, "equality");
    assert(0 == property, "equality (reversed)");

    property = 1;
    assert(property == 1, "assignment");

    skui::core::property<int> other_property = property;
    assert(property == other_property && other_property == 1, "copy assignment");

    property = 2;
    other_property = std::move(property);
    assert(other_property == 2, "move assignment");
  }

  void test_numerical_operations()
  {
    skui::core::property<int> property = 0;

    property++;
    assert(property == 1, "post-increment");
    assert(++property == 2, "pre-increment");

    property--;
    assert(property == 1, "post-decrement");
    assert(--property == 0, "pre-decrement");

    property += 1;
    assert(property == 1, "addition");

    property *= 2;
    assert(property == 2, "multiplication");

    property /= 2;
    assert(property == 1, "division");

    property -= 1;
    assert(property == 0, "subtraction");
  }

  void test_value_changed_signal()
  {
    int changed_value = 0;
    auto slot = [&changed_value](int i) { changed_value = i; };

    skui::core::property<int> property;
    property.value_changed.connect(slot);

    property = 1;

    assert(changed_value == 1, "changed slot called on assignment");
  }
}

int main()
{
  test_basic_operations();
  test_numerical_operations();
  test_value_changed_signal();
}
