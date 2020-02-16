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

#include <css/ostream.h++>

#include <css/grammar/radial_gradient.h++>

#include "css/test_rule.h++"

#include <utility>

namespace
{
  const auto circle_default = "circle";
  const auto circle_radius = "circle 5 pt";
  const auto circle_extent = "circle closest-corner";

  const auto ellipse_default = "ellipse";
  const auto ellipse_radii = "ellipse 3cm 5rem";
  const auto ellipse_extent = "ellipse farthest-side";

  const auto non_repeating_radial_gradient = "radial-gradient(ellipse at top, red, blue)";
  const auto repeating_radial_gradient = "repeating-radial-gradient(at top right, yellow 30%, green 100vw, black)";
  const auto default_shape_position_radial_gradient = "radial-gradient(#FF00FF, rgb(255,0,0))";

  const auto leading_comma = "radial-gradient(, red)";
  const auto missing_comma = "radial-gradient(at top red)";
}

int main()
{
  using skui::test::check_rule_failure;
  using skui::test::check_rule_success;

  using skui::css::grammar::circle;
  check_rule_success(circle, circle_default,
                     skui::css::radial_gradient::circle{skui::css::radial_gradient::extent::farthest_corner});
  check_rule_success(circle, circle_radius,
                     skui::css::radial_gradient::circle{skui::css::length{5, skui::css::unit::pt}});
  check_rule_success(circle, circle_extent,
                     skui::css::radial_gradient::circle{skui::css::radial_gradient::extent::closest_corner});

  using skui::css::grammar::ellipse;
  check_rule_success(ellipse, ellipse_default,
                     skui::css::radial_gradient::ellipse{skui::css::radial_gradient::extent::farthest_corner});
  check_rule_success(ellipse, ellipse_radii,
                     skui::css::radial_gradient::ellipse{skui::graphics::size2D<skui::css::length>{{3, skui::css::unit::cm},
                                                                                                   {5, skui::css::unit::rem}}});
  check_rule_success(ellipse, ellipse_extent,
                     skui::css::radial_gradient::ellipse{skui::css::radial_gradient::extent::farthest_side});

  using skui::css::grammar::radial_gradient;
  check_rule_success(radial_gradient, non_repeating_radial_gradient,
                     skui::css::radial_gradient{{false,
                                                 {{skui::css::colors::red, {}},
                                                  {skui::css::colors::blue, {}}}},
                                                skui::css::radial_gradient::ellipse{skui::css::radial_gradient::extent::farthest_corner},
                                                skui::css::top});

  check_rule_success(radial_gradient, repeating_radial_gradient,
                     skui::css::radial_gradient{{true,
                                                 {{skui::css::colors::yellow, {{30, skui::css::unit::percentage}}},
                                                  {skui::css::colors::green, {{100, skui::css::unit::vw}}},
                                                  {skui::css::colors::black, {}}}},
                                                skui::css::radial_gradient::ellipse{skui::css::radial_gradient::extent::farthest_corner},
                                                skui::css::top_right});

  check_rule_success(radial_gradient, default_shape_position_radial_gradient,
                     skui::css::radial_gradient{{false,
                                                 {{skui::css::colors::magenta, {}},
                                                  {skui::css::colors::red, {}}}},
                                                skui::css::radial_gradient::ellipse{skui::css::radial_gradient::extent::farthest_corner},
                                                skui::css::center});

  check_rule_failure(radial_gradient, leading_comma);
  check_rule_failure(radial_gradient, missing_comma);

  return skui::test::exit_code;
}
