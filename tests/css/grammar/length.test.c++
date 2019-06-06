/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
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

#include <css/grammar/length.h++>

namespace
{
  using skui::core::string;

  const string centimeter = "2cm";
  const string millimeter = "1e3mm";
  const string inch = "2e-3in";
  const string pixel = "20px";
  const string point = "12pt";
  const string pica = "300pc";

  const string em = "2e-7em";
  const string ex = "3.4ex";
  const string ch = "123ch";
  const string rem = "1rem";
  const string vw = "0.1vw";
  const string vh = "100vh";
  const string vmin = "10vmin";
  const string vmax = "20vmax";
  const string percentage = "3.4%";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  using skui::css::unit;
  using skui::css::grammar::length;
  check_rule_success(length, centimeter, {2.f, unit::cm});
  check_rule_success(length, millimeter, {1e3f, unit::mm});
  check_rule_success(length, inch, {2e-3f, unit::in});
  check_rule_success(length, pixel, {20.f, unit::px});
  check_rule_success(length, point, {12, unit::pt});
  check_rule_success(length, pica, {300.f, unit::pc});

  check_rule_success(length, em, {2e-7f, unit::em});
  check_rule_success(length, ex, {3.4f, unit::ex});
  check_rule_success(length, ch, {123.f, unit::ch});
  check_rule_success(length, rem, {1.f, unit::rem});
  check_rule_success(length, vw, {.1f, unit::vw});
  check_rule_success(length, vh, {100.f, unit::vh});
  check_rule_success(length, vmin, {10.f, unit::vmin});
  check_rule_success(length, vmax, {20.f, unit::vmax});
  check_rule_failure(length, percentage);

  using skui::css::grammar::length_percentage;
  check_rule_success(length_percentage, centimeter, {2.f, unit::cm});
  check_rule_success(length_percentage, millimeter, {1e3f, unit::mm});
  check_rule_success(length_percentage, inch, {2e-3f, unit::in});
  check_rule_success(length_percentage, pixel, {20.f, unit::px});
  check_rule_success(length_percentage, point, {12, unit::pt});
  check_rule_success(length_percentage, pica, {300.f, unit::pc});

  check_rule_success(length_percentage, em, {2e-7f, unit::em});
  check_rule_success(length_percentage, ex, {3.4f, unit::ex});
  check_rule_success(length_percentage, ch, {123.f, unit::ch});
  check_rule_success(length_percentage, rem, {1.f, unit::rem});
  check_rule_success(length_percentage, vw, {.1f, unit::vw});
  check_rule_success(length_percentage, vh, {100.f, unit::vh});
  check_rule_success(length_percentage, vmin, {10.f, unit::vmin});
  check_rule_success(length_percentage, vmax, {20.f, unit::vmax});
  check_rule_success(length_percentage, percentage, {3.4f, unit::percentage});

  return skui::test::exit_code;
}
