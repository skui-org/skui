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

#include <chrono>
#include <iostream>

std::ostream& operator<<(std::ostream& os, std::chrono::milliseconds duration)
{
  return os << duration.count() << " ms";
}

#include "css/test_rule.h++"

#include <core/string.h++>

#include <css/grammar/time.h++>

namespace
{
  using skui::core::string;

  const string milliseconds = "20.54ms";
  const string milliseconds_e = "1.2e2ms";

  const string seconds = "25.3456s";
  const string seconds_e = "2.123e-1s";

  const string not_time = "23";
  const string also_not_time = "ms";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  check_rule_success(skui::css::grammar::time, milliseconds, std::chrono::milliseconds{21});
  check_rule_success(skui::css::grammar::time, milliseconds_e, std::chrono::milliseconds{120});

  check_rule_success(skui::css::grammar::time, seconds, std::chrono::milliseconds{25346});
  check_rule_success(skui::css::grammar::time, seconds_e, std::chrono::milliseconds{212});

  check_rule_failure(skui::css::grammar::time, not_time);
  check_rule_failure(skui::css::grammar::time, also_not_time);

  return skui::test::exit_code;
}
