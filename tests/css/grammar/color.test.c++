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

#include <css/grammar/color.h++>

namespace
{
  constexpr auto named = "magenta";
  constexpr auto named_incorrect = "meganta";

  constexpr auto hex = "#150fda";
  constexpr auto hex_short = "#9A1";
  constexpr auto hex_alpha = "#A1B2C3D4";
  constexpr auto hex_alpha_short = "#103D";
  constexpr auto hex_incorrect = "#ACOLOR";

  constexpr auto rgb = "rgb(1,2%,3.5)";
  constexpr auto rgba = "rgba(1%,2,256,4.8)";
  constexpr auto rgb_incorrect = "rgb(e6,1,2)";
  constexpr auto rgba_incorrect = "rgba(1,2,3,-3)";

  constexpr auto hsl = "hsl(1,2%,.3)";
  constexpr auto hsla = "hsla(1,.2,3%,4%)";
  constexpr auto hsla_large_hue = "hsla(780, 3%, .5, 4.8)";
  constexpr auto hsla_large_saturation = "hsla(180, 110%, 0.1, .314)";
  constexpr auto hsla_large_lightness = "hsla(45, 78%, 3.14, 6.32%)";
  constexpr auto hsl_incorrect = "hsl(1,2,x)";
  constexpr auto hsla_incorrect = "hsla(1, hello, .3;)";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  using skui::css::grammar::color;

  check_rule_success(color, named, skui::css::colors::magenta);
  check_rule_failure(color, named_incorrect);

  check_rule_success(color, hex, skui::css::color{0x150FDAFF});
  check_rule_success(color, hex_short, skui::css::color{0x99AA11FF});
  check_rule_success(color, hex_alpha, skui::css::color{0xA1B2C3D4});
  check_rule_success(color, hex_alpha_short, skui::css::color{0x110033DD});
  check_rule_failure(color, hex_incorrect);

  check_rule_success(color, rgb, skui::css::color{0x010503FF});
  check_rule_success(color, rgba, skui::css::color{0x0302FFFF});
  check_rule_failure(color, rgb_incorrect);
  check_rule_failure(color, rgba_incorrect);

  check_rule_success(color, hsl, skui::css::color{0x4e4b4bFF});
  check_rule_success(color, hsla, skui::css::color{0x0906060A});
  check_rule_success(color, hsla_large_hue, skui::css::color{0x837C7CFF});
  check_rule_success(color, hsla_large_saturation, skui::css::color{0x00333350});
  check_rule_success(color, hsla_large_lightness, skui::css::color{0xFFFFFF10});
  check_rule_failure(color, hsl_incorrect);
  check_rule_failure(color, hsla_incorrect);

  return skui::test::exit_code;
}
