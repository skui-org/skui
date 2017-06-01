/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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
  using skui::test::check;

  void test_value_changed_signal()
  {
    int changed_value = 0;
    auto slot = [&changed_value](int i) { changed_value = i; };

    skui::core::property<int> property{};
    property.value_changed.connect(slot);

    property = 1;
    check(changed_value == 1, "changed slot called on assignment");

    property = std::move(2);
    check(changed_value == 2, "moving value into property emits signal");
  }

  void test_basic_operations()
  {
    bool slot_called = false;
    auto slot = [&slot_called](int) { slot_called = true; };

    skui::core::property<int> property{0};
    property.value_changed.connect(slot);

    check(property == 0, "==");
    check(0 == property, "== (reversed)");
    check(property <  1, "<" );
    check(property <= 0, "<=");
    check(property > -1, ">" );
    check(property >= 0, ">=");
    check(property != 1, "!=");
    check(!slot_called,  "operators don't emit value_changed");

    slot_called = false;
    property = 1;
    check(property == 1, "assignment");
    check(slot_called,   "assignment emits value_changed");

    slot_called = false;
    skui::core::property<int> other_property{property};
    check(property == other_property && other_property == 1, "copy construction");
    check(!slot_called, "copy construction does not emit value_changed");

    slot_called = false;
    other_property = 0;
    check(slot_called, "connection copied");

    slot_called = false;
    other_property = std::move(property);
    check(other_property == 1, "move assignment moves value");
    check(!slot_called, "move constructor does not emit value_changed");

    slot_called = false;
    property = 0;
    check(!slot_called, "moved-from property is disconnected");

    slot_called = false;
    other_property = 0;
    check(slot_called, "moved-to property is connected");
  }
}

int main()
{
  test_value_changed_signal();
  test_basic_operations();

  return skui::test::exit_code;
}
