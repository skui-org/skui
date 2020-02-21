/**
 * The MIT License (MIT)
 *
 * Copyright © 2020 Ruben Van Boxem
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

#include <css/grammar/clear.h++>

namespace
{
  constexpr auto none = "none";
  constexpr auto left = "left";
  constexpr auto right = "right";
  constexpr auto both = "both";

  namespace x3 = boost::spirit::x3;
  const auto clear = x3::rule<struct clear, skui::css::property<skui::css::clear>>{"clear"}
                        = skui::css::grammar::clear;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(clear, none, skui::css::clear::none);
  check_rule_success(clear, left, skui::css::clear::left);
  check_rule_success(clear, right, skui::css::clear::right);
  check_rule_success(clear, both, skui::css::clear::both);

  return skui::test::exit_code;
}
