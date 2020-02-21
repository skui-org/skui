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

#include <css/grammar/linear_gradient.h++>

namespace
{
  const auto direction = "to top";
  const auto angle = "1.25 turn";

  const auto non_repeating_linear_gradient = "linear-gradient(to right, red, blue)";
  const auto repeating_linear_gradient = "repeating-linear-gradient(to bottom left, yellow 30%, green 100vw, black)";
  const auto default_direction_linear_gradient = "linear-gradient(#FF00FF, rgb(255,0,0))";

  const auto leading_comma = "linear-gradient(, red)";
  const auto missing_comma = "linear-gradient(to top red)";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  using skui::css::grammar::direction_or_angle;
  check_rule_success(direction_or_angle, direction, skui::css::top);
  check_rule_success(direction_or_angle, angle, 450.f);

  using skui::css::grammar::linear_gradient;
  check_rule_success(linear_gradient, non_repeating_linear_gradient,
                     skui::css::linear_gradient{{false,
                                                 {{skui::css::colors::red, {}},
                                                  {skui::css::colors::blue, {}}}},
                                                skui::css::right});
  check_rule_success(linear_gradient, repeating_linear_gradient,
                     skui::css::linear_gradient{{true,
                                                 {{skui::css::colors::yellow, skui::css::length{30, skui::css::unit::percentage}},
                                                  {skui::css::colors::green, skui::css::length{100, skui::css::unit::vw}},
                                                  {skui::css::colors::black, {}}}},
                                                skui::css::bottom_left});
  check_rule_success(linear_gradient, default_direction_linear_gradient,
                     skui::css::linear_gradient{{false,
                                                 {{skui::css::colors::fuchsia, {}},
                                                  {skui::css::colors::red, {}}}},
                                                skui::css::top});

  check_rule_failure(linear_gradient, leading_comma);
  check_rule_failure(linear_gradient, missing_comma);

  return skui::test::exit_code;
}
