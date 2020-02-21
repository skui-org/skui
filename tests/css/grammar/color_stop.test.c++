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

#include <css/grammar/color_stop.h++>

namespace
{
  const auto color = "red";

  const auto color_percentage = "blue 5.4%";
  const auto color_length = "green .3in";

  const auto color_angle = "yellow .5turn";
}

int main()
{
  using skui::test::check_rule_success;

  using skui::css::grammar::linear_color_stop;
  check_rule_success(linear_color_stop, color, {skui::css::colors::red, {}});
  check_rule_success(linear_color_stop, color_percentage, {skui::css::colors::blue, skui::css::length{5.4f, skui::css::unit::percentage}});
  check_rule_success(linear_color_stop, color_length, {skui::css::colors::green, skui::css::length{.3f, skui::css::unit::in}});

  using skui::css::grammar::angular_color_stop;
  check_rule_success(angular_color_stop, color, {skui::css::colors::red, {}});
  check_rule_success(angular_color_stop, color_angle, {skui::css::colors::yellow, 180.f});

  return skui::test::exit_code;
}
