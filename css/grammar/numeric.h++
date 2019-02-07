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

#ifndef SKUI_CSS_GRAMMAR_NUMERIC_H
#define SKUI_CSS_GRAMMAR_NUMERIC_H

#include "css/grammar/as.h++"
#include "css/grammar/semantic_checks.h++"
#include "css/grammar/semantic_math.h++"

#include <core/debug.h++>

#include <boost/spirit/home/x3.hpp>

#include <cmath>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  template<int max_value>
  constexpr auto clamp_and_normalize = [](auto& context)
  {
    using value_type = std::remove_reference_t<decltype(x3::_val(context))>;
    using attribute_type = std::remove_reference_t<decltype(x3::_attr(context))>;

    x3::_val(context) = value_type(std::clamp<attribute_type>(x3::_attr(context), 0, max_value)/attribute_type(max_value));
  };

  constexpr auto uint8_hex = x3::uint_parser<std::uint8_t, 16, 2, 2>{};
  const auto ufloat = x3::real_parser<float, x3::ureal_policies<float>>{};

  template<typename ValueType>
  struct non_scientific_real_policies : x3::real_policies<ValueType>
  {
    template<typename Iterator>
    static bool parse_exp(Iterator&, const Iterator&)
    {
      return false;
    }
  };
  const auto non_scientific_float = x3::real_parser<float, non_scientific_real_policies<float>>{};

  const auto percentage = x3::rule<struct percentage, float>{"percentage"}
                       %= (x3::float_ >> '%')[divide{100.f}];

  const auto percentage_or_uint8 = x3::rule<struct percentage_or_uint8, std::uint8_t>{"percentage or uint8"}
                                %= as<float>(percentage[clamp{1.f}][multiply{255.f}][round])
                                 | as<float>(ufloat[clamp{255.f}])
                                 ;
  const auto percentage_or_normalized = x3::rule<struct percentage_or_normalized, float>{"percentage or normalized"}
                                     %= percentage[clamp{1.f}]
                                      | ufloat[clamp{1.f}]
                                      ;
  const auto degrees_normalized = x3::rule<struct degrees_normalized, float>{"degrees [0,360] normalized to [0,1]"}
                               %= ufloat[clamp_and_normalize<360>];
}

#endif
