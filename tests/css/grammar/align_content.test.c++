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

#include <css/grammar/align_content.h++>


namespace
{
  const auto stretch = "stretch";
  const auto center = "center";
  const auto flex_start = "flex-start";
  const auto flex_end = "flex-end";
  const auto space_between = "space-between";
  const auto space_around = "space-around";

  namespace x3 = boost::spirit::x3;
  const auto align_content = x3::rule<struct align_content, skui::css::property<skui::css::align_content>>{"align-content"}
                           = skui::css::grammar::align_content;
}

int main()
{
  using skui::test::check_rule_failure;
  using skui::test::check_rule_success;

  check_rule_failure(align_content, "auto");
  check_rule_success(align_content, stretch, skui::css::align_content::stretch);
  check_rule_success(align_content, center, skui::css::align_content::center);
  check_rule_success(align_content, flex_start, skui::css::align_content::flex_start);
  check_rule_success(align_content, flex_end, skui::css::align_content::flex_end);
  check_rule_success(align_content, space_between, skui::css::align_content::space_between);
  check_rule_success(align_content, space_around, skui::css::align_content::space_around);

  return skui::test::exit_code;
}
