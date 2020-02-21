/**
 * The MIT License (MIT)
 *
 * Copyright © 2019-2020 Ruben Van Boxem
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

#include <css/grammar/semantic/convert_to.h++>

namespace
{
  namespace x3 = boost::spirit::x3;

  using skui::css::grammar::convert_to;

  struct constructible_from_int
  {
    explicit constructible_from_int(int i = 0) : v{i} {}
    int v;
  };

  struct constructible_from_float
  {
    explicit constructible_from_float(float f = 0.f) : v{f} {}
    float v;
  };

  bool operator==(const constructible_from_int& lhs, const constructible_from_int& rhs)
  {
    return lhs.v == rhs.v;
  }
  bool operator==(const constructible_from_float& lhs, const constructible_from_float& rhs)
  {
    return lhs.v == rhs.v;
  }

  std::ostream& operator<<(std::ostream& os, const constructible_from_int& c)
  {
    return os << c.v;
  }
  std::ostream& operator<<(std::ostream& os, const constructible_from_float& c)
  {
    return os << c.v;
  }


  const auto conversion1 = x3::rule<struct conversion1, constructible_from_int>{"conversion1"}
                         = x3::int_[convert_to<constructible_from_int>{}];

  const auto conversion2 = x3::rule<struct conversion2, constructible_from_float>{"conversion2"}
                         = x3::int_[convert_to<constructible_from_float, float>{}];

  constexpr auto integer = "42";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  check_rule_success(conversion1, integer, constructible_from_int{42});
  check_rule_success(conversion2, integer, constructible_from_float{42.f});

  return skui::test::exit_code;
}
