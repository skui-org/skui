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

#include <css/grammar/box_decoration_break.h++>


namespace
{
  const auto slice = "slice";
  const auto clone_ = "clone";

  namespace x3 = boost::spirit::x3;
  const auto box_decoration_break = x3::rule<struct box_decoration_break, skui::css::property<skui::css::box_decoration_break>>{"box-decoration-break"}
                                  = skui::css::grammar::box_decoration_break;
}

int main()
{
  using skui::test::check_rule_success;

  check_rule_success(box_decoration_break, slice, skui::css::box_decoration_break::slice);
  check_rule_success(box_decoration_break, clone_, skui::css::box_decoration_break::clone);

  return skui::test::exit_code;
}
