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

#include "css/ostream.h++"
#include "css/test_rule.h++"

#include <css/grammar/timing_function.h++>

namespace
{
  using skui::core::string;

  const string ease = "ease";
  const string linear = "linear";
  const string ease_in = "ease-in";
  const string ease_out = "ease-out";
  const string ease_in_out = "ease-in-out";
  const string cubic_bezier = "cubic-bezier(.1, .2, .3, .4)";

  const string step_start = "step-start";
  const string step_end = "step-end";
  const string steps = "steps(2, end)";

  namespace x3 = boost::spirit::x3;

  const auto timing_function = x3::rule<struct timing_function, skui::css::timing_function>{"timing-function"}
                             = skui::css::grammar::timing_function;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(timing_function, ease, skui::css::cubic_bezier{.25f, .1f, .25f, 1});
  check_rule_success(timing_function, linear, skui::css::cubic_bezier{0, 0, 1, 1});
  check_rule_success(timing_function, ease_in, skui::css::cubic_bezier{.42f, 0, 1, 1});
  check_rule_success(timing_function, ease_out, skui::css::cubic_bezier{0, 0, .58f, 1});
  check_rule_success(timing_function, ease_in_out, skui::css::cubic_bezier{.42f, 0, .58f, 1});
  check_rule_success(timing_function, cubic_bezier, skui::css::cubic_bezier{.1f, .2f, .3f, .4f});

  check_rule_success(timing_function, step_start, skui::css::steps{1, skui::css::steps::start});
  check_rule_success(timing_function, step_end, skui::css::steps{1, skui::css::steps::end});
  check_rule_success(timing_function, steps, skui::css::steps{2, skui::css::steps::end});

  return skui::test::exit_code;
}
