/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2020 Ruben Van Boxem
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

#include "css/ostream.h++"
#include "css/test_rule.h++"

#include <css/grammar/property_symbols_table.h++>

enum class Enum
{
  one,
  two
};

std::ostream& operator<<(std::ostream& os, Enum e)
{
  switch(e)
  {
    case Enum::one:
      return os << "one";
    case Enum::two:
      return os << "two";
  }
  return os;
}

namespace
{
  constexpr auto inherit = "inherit";
  constexpr auto initial = "initial";
  constexpr auto one = "one";
  constexpr auto two = "two";

  struct enum_table : skui::css::grammar::property_symbols_table<Enum>
  {
    enum_table()
    {
      add("one", Enum::one)
         ("two", Enum::two)
         ;
    }
  } const enum_parser;

  namespace x3 = boost::spirit::x3;
  const auto enum_rule = x3::rule<struct enum_rule, skui::css::property<Enum>>{"enum rule"}
                       = enum_parser;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(enum_rule, inherit, skui::css::inherit);
  check_rule_success(enum_rule, initial, skui::css::initial);
  check_rule_success(enum_rule, one, Enum::one);
  check_rule_success(enum_rule, two, Enum::two);

  return skui::test::exit_code;
}
