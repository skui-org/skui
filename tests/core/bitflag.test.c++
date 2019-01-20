/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

enum class test
{
  one, two, three, four
};
using test_flag = skui::core::bitflag<test>;

enum class flag
{
  one = 0x1,
  two = 0x2,
  three = 0x4,
  four = 0x8,
  five = 0x10
};
namespace skui
{
  namespace core
  {
    template<> struct enum_is_bitflag<flag> : std::true_type {};
  }
}
using real_flag = skui::core::bitflag<flag>;

namespace
{
  using skui::test::check;
  using namespace skui::core::bitflag_operators;

  void test_bitflag_set_test()
  {
    test_flag tester(test::one);

    check( tester.test(test::one), "Construction sets proper bit.");
    check(!tester.test(test::two), "Construction doesn't set improper bit.");
    check(!tester.test(test::three), "Construction doesn't set improper bit.");
    check( tester.count() == 1, "Count with one bit set returns correct value.");

    tester.set(test::three);

    check( tester.test(test::one), "Set leaves previously set bit set.");
    check(!tester.test(test::two), "Set leaves unrelated bit unset.");
    check( tester.test(test::three), "Set sets new bit.");
    check( tester.count() == 2, "Count with two bits set returns correct value.");

    tester.unset(test::one);

    check(!tester.test(test::one), "Unset unsets previously set bit.");
    check(!tester.test(test::two), "Unset leaves unrelated bit unset.");
    check( tester.test(test::three), "Unset leaves unrelated bit set.");
    check( tester.count() == 1, "Unset resultsin correct count.");
  }

  void test_bitflag_or_and()
  {
    test_flag tester = test::one | test::two;

    tester |= test::four;

    check(  tester.test(test::one), "First bitflag is set.");
    check(  tester & test::two, "Second bitflag is set.");
    check(!(tester & test::three), "Third bitflag is set.");
    check(  tester & test::four, "Fourth bitflag is set.");
    check(  tester.count() == 3, "OR operators set correct number of bits.");
  }

  void test_bitflag_clear()
  {
    test_flag tester = test::one | test::two;

    tester.clear();

    check(!tester.test(test::one), "Clear unsets set bit.");
    check(!tester.test(test::two), "Clear unsets other set bit.");
    check(!tester.test(test::three), "Clear leaves unset bit unset.");
    check(!tester.test(test::four), "Clear leaves unset bit unset.");

    check( tester.count() == 0, "Clearing bitflag unsets all bits.");
  }

  void test_bitflag_real_bitflag()
  {
    real_flag tester = flag::three | flag::two;

    check(!tester.test(flag::one), "Real bitflag sets first bit correctly.");
    check( tester.test(flag::two), "Real bitflag sets second bit correctly.");
    check( tester.test(flag::three), "Real bitflag leaves third bit unset.");
    check(!tester.test(flag::four), "Real bitflag leaves fourth bit unset.");
    check(!tester.test(flag::five), "Real bitflag leaves fifth bit unset.");
    check( tester.count() == 2, "real bitflag sets correct number of bits.");
  }
}

int main()
{
  test_bitflag_set_test();
  test_bitflag_or_and();
  test_bitflag_clear();
  test_bitflag_real_bitflag();
}
