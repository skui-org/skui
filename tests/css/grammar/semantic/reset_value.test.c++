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

#include "css/test_rule.h++"

#include <css/grammar/semantic/reset_value.h++>

namespace
{
  using skui::core::string;
  using skui::css::grammar::reset_value;

  const string one = "1";
  const string two = "1 2";

  using namespace boost::spirit::x3;

  const auto one_or_two = rule<struct one_or_two, std::vector<int>, true>{"one or two"}
                        = int_ >> int_
                        | eps[reset_value] >> int_ >> attr(1)
                        ;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(one_or_two, one, {1, 1});
  check_rule_success(one_or_two, two, {1, 2});

  return skui::test::exit_code;
}
