/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#include <core/string.h++>
#include <css/grammar/color.h++>

namespace
{
  using skui::core::string;

  const string named = "magenta";
  const string named_incorrect = "meganta";

  const string hex = "#150fda";
  const string hex_short = "#9A1";
  const string hex_alpha = "#A1B2C3D4";
  const string hex_alpha_short = "#103D";
  const string hex_incorrect = "#ACOLOR";

  const string rgb = "rgb(1,2%,3.5)";
  const string rgba = "rgba(1%,2,256,4.8)";
  const string rgb_incorrect = "rgb(e6,1,2)";
  const string rgba_incorrect = "rgba(1,2,3,-3)";

  const string hsl = "hsl(1,2%,.3)";
  const string hsla = "hsla(1,.2,3%,4%)";
  const string hsla_large_hue = "hsla(780, 3%, .5, 4.8)";
  const string hsla_large_saturation = "hsla(180, 110%, 0.1, .314)";
  const string hsla_large_lightness = "hsla(45, 78%, 3.14, 6.32%)";
  const string hsl_incorrect = "hsl(1,2,x)";
  const string hsla_incorrect = "hsla(1, hello, .3;)";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;
  using skui::css::grammar::color;
  using skui::css::grammar::shorthand_hex;

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
