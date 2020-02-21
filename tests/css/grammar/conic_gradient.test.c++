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

#include <css/grammar/conic_gradient.h++>

namespace
{
  const auto from = "conic-gradient(from 5deg, red, blue)";
  const auto repeating_at = "repeating-conic-gradient(at center, pink, blue)";
  const auto from_at = "conic-gradient(from .5turn at bottom left, green, yellow)";
  const auto repeating_colors = "conic-gradient(red, green, blue)";

  const auto leading_comma = "conic-gradient(,red)";
  const auto missing_comma = "conic-gradient(at top yellow)";
}

int main()
{
  using skui::test::check_rule_failure;
  using skui::test::check_rule_success;

  using skui::css::grammar::conic_gradient;

  check_rule_success(conic_gradient, from, skui::css::conic_gradient{{false,
                                                                      {{skui::css::colors::red, {}},
                                                                      {skui::css::colors::blue, {}}}},
                                                                     5,
                                                                     skui::css::top_left});
  check_rule_success(conic_gradient, repeating_at, skui::css::conic_gradient{{true,
                                                                             {{skui::css::colors::pink, {}},
                                                                              {skui::css::colors::blue, {}}}},
                                                                             0,
                                                                             skui::css::center});
  check_rule_success(conic_gradient, from_at, skui::css::conic_gradient{{false,
                                                                         {{skui::css::colors::green, {}},
                                                                          {skui::css::colors::yellow, {}}}},
                                                                         180,
                                                                         skui::css::bottom_left});
  check_rule_success(conic_gradient, repeating_colors, skui::css::conic_gradient{{true,
                                                                                  {{skui::css::colors::red, {}},
                                                                                   {skui::css::colors::green, {}},
                                                                                   {skui::css::colors::blue, {}}}},
                                                                                  0,
                                                                                  skui::css::top_left});

  check_rule_failure(conic_gradient, leading_comma);
  check_rule_failure(conic_gradient, missing_comma);

  return skui::test::exit_code;
}
