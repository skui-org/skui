/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#include "css/test_rule.h++"

#include <css/grammar/semantic_factory.h++>

namespace
{
  using skui::core::string;
  using skui::test::check_rule_success;
  using skui::test::check;
  using namespace boost::spirit::x3;
  using skui::css::grammar::factory;

  class two_ints
  {
  public:
    two_ints() = default;

    static two_ints create(int a, int b)
    {
      return two_ints(a, b);
    }

    bool operator==(const two_ints& other) const
    {
      return other.a == a
          && other.b == b;
    }

    friend std::ostream& operator<<(std::ostream&, const two_ints&);

  private:
    two_ints(int a, int b) : b{b}, a{a} {}

    int b;
    int a;
  };

  std::ostream& operator<<(std::ostream& os, const two_ints& ints)
  {
    return os << ints.a << ", " << ints.b;
  }

  const auto two_ints_rule = rule<struct two_ints_rule, two_ints>{"two ints"}
                           = (int_ >> int_)[factory(&two_ints::create)];

  void test_semantic_factory()
  {
    const string input = "1 2";

    check_rule_success(two_ints_rule, input, two_ints::create(1, 2));
  }
}

int main()
{
  test_semantic_factory();

  return skui::test::exit_code;
}
