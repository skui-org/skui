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

#include "core/proxy_property.h++"

namespace
{
  using skui::test::assert;

  int value;
  int getter() { return value; }
  void setter(int new_value) { value = new_value; }

  void test_value_changed_signal()
  {
    bool slot_called = false;
    skui::core::proxy_property<int> property(&setter, &getter);
    property.value_changed.connect([&slot_called](int) { slot_called = true; });

    value = 0;
    property = 1;

    assert(value == 1, "proxied object changed through proxy_property.");
    assert(slot_called, "changing property emits signal.");
  }

  void test_basic_operations()
  {
    bool slot_called = false;
    skui::core::proxy_property<int> property(&setter, &getter);
    property.value_changed.connect([&slot_called](int) { slot_called = true; });

    value = 2;
    assert(property == 2, "==");
    assert(2 == property, "== (reversed)");
    assert(property <  3, "<" );
    assert(property <= 2, "<=");
    assert(property >  1, ">" );
    assert(property >= 2, ">=");
    assert(property != 1, "!=");
    assert(!slot_called,  "operators don't emit value_changed");

    property = 1;
    assert(property == 1, "assignment");
    assert(value == 1,    "assignment (underlying value)");
    assert(slot_called,   "assignment emits value_changed");

    slot_called = false;
    skui::core::proxy_property<int> other_property{property};
    assert(property == other_property && other_property == 1, "copy construction");
    assert(!slot_called, "copy construction does not emit value_changed");

    slot_called = false;
    other_property = 0;
    assert(slot_called, "connection copied");

    slot_called = false;
    other_property = std::move(property);
    assert(!slot_called, "move constructor does not emit value_changed");

    slot_called = false;
    other_property = 2;
    assert(slot_called, "moved-to property is connected");
    assert(value == 2,  "moved-to property changes external value");
  }
}

int main()
{
  test_value_changed_signal();
  test_basic_operations();
}
