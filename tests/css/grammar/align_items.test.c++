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

#include "css/test_rule.h++"

#include <css/grammar/align_items.h++>

#include <css/ostream.h++>

namespace
{
  const auto stretch = "stretch";
  const auto center = "center";
  const auto flex_start = "flex-start";
  const auto flex_end = "flex-end";
  const auto baseline = "baseline";

  namespace x3 = boost::spirit::x3;
  const auto align_items = x3::rule<struct align_items, skui::css::property<skui::css::align_items>>{"align-items"}
                         = skui::css::grammar::align_items;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(align_items, stretch, skui::css::align_items::stretch);
  check_rule_success(align_items, center, skui::css::align_items::center);
  check_rule_success(align_items, flex_start, skui::css::align_items::flex_start);
  check_rule_success(align_items, flex_end, skui::css::align_items::flex_end);
  check_rule_success(align_items, baseline, skui::css::align_items::baseline);

  return skui::test::exit_code;
}
