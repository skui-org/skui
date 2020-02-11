/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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

#include <css/grammar/numeric.h++>

#include <core/string.h++>

namespace
{
  using skui::core::string;

  using boost::spirit::x3::rule;

  const auto uint8 = rule<struct uint8, std::uint8_t>{"uint8"}
                   = boost::spirit::x3::uint8;
  const auto uint8_hex = rule<struct uint8_hex, std::uint8_t>{"uint8 hex"}
                       = skui::css::grammar::uint8_hex;
  const auto ufloat = rule<struct ufloat, float>{"ufloat"}
                    = skui::css::grammar::ufloat;
  const auto non_scientific_float = rule<struct non_scientific_float>{"non-scientific float"}
                                  = skui::css::grammar::non_scientific_float;

  const string positive = "123";
  const string negative = "-123";
  const string decimal = "12.3";
  const string hex = "AB";
  const string text = "text";


  const string percentage_integral = "76%";
  const string percentage_decimal = "23.4%";
  const string percentage_higher = "112%";
  const string percentage_negative = "-5%";

  const string scientific = "1e-5";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  std::cout << std::hex;

  check_rule_success(uint8, positive, 123);
  check_rule_failure(uint8, negative);
  check_rule_failure(uint8, decimal);
  check_rule_failure(uint8, hex);
  check_rule_failure(uint8, text);
  check_rule_failure(uint8, percentage_integral);
  check_rule_failure(uint8, percentage_decimal);
  check_rule_failure(uint8, percentage_higher);
  check_rule_failure(uint8, percentage_negative);

  check_rule_success(ufloat, positive, 123);
  check_rule_failure(ufloat, negative);
  check_rule_success(ufloat, decimal, 12.3f);
  check_rule_failure(ufloat, hex);
  check_rule_failure(ufloat, text);
  check_rule_failure(ufloat, percentage_integral);
  check_rule_failure(ufloat, percentage_decimal);
  check_rule_failure(ufloat, percentage_higher);
  check_rule_failure(ufloat, percentage_negative);

  check_rule_failure(uint8_hex, positive);
  check_rule_failure(uint8_hex, negative);
  check_rule_failure(uint8_hex, decimal);
  check_rule_success(uint8_hex, hex, 0xAB);
  check_rule_failure(uint8_hex, text);
  check_rule_failure(uint8_hex, percentage_integral);
  check_rule_failure(uint8_hex, percentage_decimal);
  check_rule_failure(uint8_hex, percentage_higher);
  check_rule_failure(uint8_hex, percentage_negative);

  using skui::css::grammar::percentage;
  check_rule_failure(percentage, positive);
  check_rule_failure(percentage, negative);
  check_rule_failure(percentage, decimal);
  check_rule_failure(percentage, hex);
  check_rule_failure(percentage, text);
  check_rule_success(percentage, percentage_integral, .76f);
  check_rule_success(percentage, percentage_decimal, .234f);
  check_rule_success(percentage, percentage_higher, 1.12f);
  check_rule_success(percentage, percentage_negative, -.05f);

  using skui::css::grammar::percentage_or_uint8_as_float;
  check_rule_success(percentage_or_uint8_as_float, positive, 123.f/255);
  check_rule_failure(percentage_or_uint8_as_float, negative);
  check_rule_success(percentage_or_uint8_as_float, decimal, 12.f/255);
  check_rule_failure(percentage_or_uint8_as_float, hex);
  check_rule_failure(percentage_or_uint8_as_float, text);
  check_rule_success(percentage_or_uint8_as_float, percentage_integral, .76f);
  check_rule_success(percentage_or_uint8_as_float, percentage_decimal, .234f);
  check_rule_success(percentage_or_uint8_as_float, percentage_higher, 1.f);
  check_rule_success(percentage_or_uint8_as_float, percentage_negative, 0.f);

  using skui::css::grammar::percentage_or_normalized;
  check_rule_success(percentage_or_normalized, positive, 1);
  check_rule_failure(percentage_or_normalized, negative);
  check_rule_success(percentage_or_normalized, decimal, 1);
  check_rule_failure(percentage_or_normalized, hex);
  check_rule_failure(percentage_or_normalized, text);
  check_rule_success(percentage_or_normalized, percentage_integral, 76.f/100);
  check_rule_success(percentage_or_normalized, percentage_decimal, 23.4f/100);
  check_rule_success(percentage_or_normalized, percentage_higher, 1);
  check_rule_success(percentage_or_normalized, percentage_negative, 0);

  using skui::css::grammar::degrees_normalized;
  check_rule_success(degrees_normalized, positive, 123.f/360.f);
  check_rule_failure(degrees_normalized, negative);
  check_rule_success(degrees_normalized, decimal, 12.3f/360.f);
  check_rule_failure(degrees_normalized, hex);
  check_rule_failure(degrees_normalized, text);
  check_rule_failure(degrees_normalized, percentage_integral);
  check_rule_failure(degrees_normalized, percentage_decimal);
  check_rule_failure(degrees_normalized, percentage_higher);
  check_rule_failure(degrees_normalized, percentage_negative);

  check_rule_failure(non_scientific_float, scientific);

  return skui::test::exit_code;
}
