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

#include <css/grammar/semantic/repeat_value.h++>

namespace
{
  using skui::core::string;
  using skui::css::grammar::repeat_value;
  namespace x3 = boost::spirit::x3;

  const string one = "1.2";
  const string two = "1.2 3.4";

  const auto one_to_four = x3::rule<struct one_to_four, std::vector<double>, true>{"one to four"}
                         = (x3::double_ >> x3::eps)[repeat_value<0,0,0>];
  const auto two_to_six = x3::rule<struct two_to_six, std::vector<double>, true>{"two to six"}
                        = (x3::double_ >> x3::double_)[repeat_value<0,1,1,0>];
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(one_to_four, one, {1.2, 1.2, 1.2, 1.2});
  check_rule_success(two_to_six, two, {1.2, 3.4, 1.2, 3.4, 3.4, 1.2});

  return skui::test::exit_code;
}
