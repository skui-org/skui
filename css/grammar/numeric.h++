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

#ifndef SKUI_CSS_GRAMMAR_NUMERIC_H
#define SKUI_CSS_GRAMMAR_NUMERIC_H

#include "css/grammar/semantic_checks.h++"
#include "css/grammar/semantic_math.h++"

#include <core/debug.h++>

#include <boost/spirit/home/x3.hpp>

#include <cmath>

namespace skui::css::grammar
{
  using namespace boost::spirit::x3;

  template<int max_value>
  constexpr auto clamp = [](auto& context)
  {
    using value_type = std::remove_reference_t<decltype(_val(context))>;
    using attribute_type = std::remove_reference_t<decltype(_attr(context))>;

    _val(context) = value_type(std::clamp<attribute_type>(_attr(context), 0, max_value));
  };
  template<int max_value>
  constexpr auto normalize = [](auto& context)
  {
    using value_type = std::remove_reference_t<decltype(_val(context))>;
    using attribute_type = std::remove_reference_t<decltype(_attr(context))>;

    _val(context) = value_type(_attr(context)/attribute_type(max_value));
  };
  template<int max_value>
  constexpr auto clamp_and_normalize = [](auto& context)
  {
    using value_type = std::remove_reference_t<decltype(_val(context))>;
    using attribute_type = std::remove_reference_t<decltype(_attr(context))>;

    _val(context) = value_type(std::clamp<attribute_type>(_attr(context), 0, max_value)/attribute_type(max_value));
  };

  constexpr auto multiply_by_255 = [](auto& context)
  {
    multiply_by(255, context);
  };
  constexpr auto multiply_by_17 = [](auto& context) { multiply_by(17, context); };

  constexpr auto uint8_hex = uint_parser<std::uint8_t, 16, 2, 2>{};
  const auto ufloat = real_parser<float, ureal_policies<float>>{};

  const auto percentage = rule<struct percentage, float>{"percentage"}
                        = (float_ >> '%')[normalize<100>];
  const auto normalized_percentage = rule<struct normalized_percentage, float>{"normalized_percentage"}
                                   = percentage[ensure_normalized];

  const auto percentage_clamped = rule<struct percentage_as_uint, float>{"percentage clamped"}
                                 = percentage[clamp<1>];
  const auto percentage_or_uint8 = rule<struct percentage_or_uint8, std::uint8_t>{"percentage or uint8"}
                                = percentage_clamped[multiply_by_255]
                                | ufloat[clamp<255>]
                                ;
  const auto percentage_or_normalized = rule<struct percentage_or_normalized, float, true>{"percentage or normalized"}
                                      = percentage[clamp<1>]
                                      | ufloat[clamp_and_normalize<1>]
                                      ;
  const auto degrees_normalized = rule<struct degrees_normalized, float>{"degrees [0,360] normalized to [0,1]"}
                                = ufloat[clamp_and_normalize<360>];
}

#endif
