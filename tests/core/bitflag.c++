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

#include <core/bitflag.h++>

namespace
{
  using skui::test::assert;
  using namespace skui::core::bitflag_operators;

  enum class test
  {
    one, two, three, four
  };
  using test_flag = skui::core::bitflag<test>;

  void test_bitflag_set_test()
  {
    test_flag tester(test::one);

    assert( tester.test(test::one), "Construction sets proper bit.");
    assert(!tester.test(test::two), "Construction doesn't set improper bit.");
    assert(!tester.test(test::three), "Construction doesn't set improper bit.");

    tester.set(test::three);

    assert( tester.test(test::one), "Set leaves previously set bit set.");
    assert(!tester.test(test::two), "Set leaves unrelated bit unset.");
    assert( tester.test(test::three), "Set sets new bit.");

    tester.unset(test::one);

    assert(!tester.test(test::one), "Unset unsets previously set bit.");
    assert(!tester.test(test::two), "Unset leaves unrelated bit unset.");
    assert( tester.test(test::three), "Unset leaves unrelated bit set.");
  }

  void test_bitflag_or_and()
  {
    test_flag tester = test::one | test::two;

    tester |= test::four;

    assert(  tester.test(test::one), "First bitflag is set.");
    assert(  tester & test::two, "Second bitflag is set.");
    assert(!(tester & test::three), "Third bitflag is set.");
    assert(  tester & test::four, "Fourth bitflag is not set.");
  }
}

int main()
{
  test_bitflag_set_test();
  test_bitflag_or_and();
}
