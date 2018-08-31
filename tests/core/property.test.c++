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

#include "core/property.h++"

namespace
{
  using skui::test::check;

  void test_construct_with_slots()
  {
    bool changed = false;
    auto property_changed = [&changed] { changed = true; };
    skui::core::property<int> property(0, property_changed);

    property = 1;

    check(changed, "slot passed to constructor connected");
  }

  void test_bitwise_operators()
  {
    bool slot_called = false;
    auto slot = [&slot_called](int) { slot_called = true; };

    skui::core::property<int> property{3};
    property.value_changed.connect(slot);

    check((property | 1) == 3, "bitwise or with value");
    check((property & 1) == 1, "bitwise and with value");
    check((property ^ 1) == 2, "bitwise xor with value");
    check(property == 3, "bitwise operators don't change value");
    check(!slot_called, "bitwise operators don't emit signal");

    property |= 2;
    check(property == 3, "bitwise or assignment correctly not modifying value");
    check(!slot_called, "bitwise or assignment correctly not emitting signal");

    property |= 4;
    check(property == 7, "bitwise or assignment correctly modifying value");
    check(slot_called, "bitwise or assignment correctly emitting signal");
    slot_called = false;

    property &= 7;
    check(property == 7, "bitwise and correctly not modifying value");
    check(!slot_called, "bitwise and correctly not emitting signal");

    property &= 1;
    check(property == 1, "bitwise and correctly modifying value");
    check(slot_called, "bitwise and correctly emitting signal");
    slot_called = false;

    property ^= 0;
    check(property == 1, "bitwise xor correctly not modifying value");
    check(!slot_called, "bitwise xor correctly not emitting signal");

    property ^= 2;
    check(property == 3, "bitwise xor correctly modifying value");
    check(slot_called, "bitwise xor correctly emitting signal");
  }
}

int main()
{
  skui::test::run_all_property_tests<skui::core::property<int>>();

  test_construct_with_slots();
  test_bitwise_operators();

  return skui::test::exit_code;
}
