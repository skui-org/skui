/**
 * The MIT License (MIT)
 *
 * Copyright © 2020 Ruben Van Boxem
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

#include <css/grammar/box_shadow.h++>


namespace
{
  //box-shadow: none;
  const auto offsets_color = "60px -16px teal";
  const auto offsets_blur_color = "10px 5px 5px black";
  const auto offsets_blur_spread_color = "2px 2px 2px 1px rgba(0, 0, 0, 0.2)";
  const auto inset_offsets_color = "inset 5em 1em gold";
  const auto multiple_shadows = "3px 3px red, -1em 0 0.4em olive";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::css::unit;
  using skui::css::color;
  using namespace skui::css::colors;

  using skui::css::grammar::box_shadow;
  check_rule_success(box_shadow, offsets_color, {skui::css::box_shadow{false, {60.f, unit::px}, {-16.f, unit::px}, {}, {}, teal}});
  check_rule_success(box_shadow, offsets_blur_color, {skui::css::box_shadow{false, {10, unit::px}, {5, unit::px}, {5, unit::px}, {}, black}});
  check_rule_success(box_shadow, offsets_blur_spread_color, {skui::css::box_shadow{false, {2, unit::px}, {2, unit::px}, {2, unit::px}, {1, unit::px}, color::rgbaf(0,0,0,.2f)}});
  check_rule_success(box_shadow, inset_offsets_color, {skui::css::box_shadow{true, {5, unit::em}, {1, unit::em}, {}, {}, gold}});
  return skui::test::exit_code;
}
