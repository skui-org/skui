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

#ifndef SKUI_CSS_GRAMMAR_COLOR_H
#define SKUI_CSS_GRAMMAR_COLOR_H

#include "css/color.h++"

#include "css/grammar/as.h++"
#include "css/grammar/semantic_factory.h++"
#include "css/grammar/numeric.h++"

#include "css/property/align_self.h++"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

#include <cstdint>

BOOST_FUSION_ADAPT_STRUCT(skui::css::color,
                          red, green, blue, alpha)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  // Named colors
  struct named_color_table : public x3::symbols<css::color>
  {
    named_color_table();
  } const named_color;

  // Hex specification
  const auto shorthand_hex = x3::rule<struct shorthand_hex, std::uint8_t>{"shorthand hex digit"}
                          %= x3::uint_parser<std::uint8_t, 16, 1, 1>{}[multiply{std::uint8_t{17}}];

  const auto color_hex_alpha = x3::rule<struct hex_alpha, css::color>{"8 digit hex color (extension)"}
                             = uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex;
  const auto color_hex = x3::rule<struct hex, css::color>{"6 digit hex color"}
                       = uint8_hex >> uint8_hex >> uint8_hex >> x3::attr(255);
  const auto color_short_hex_alpha = x3::rule<struct short_hex_alpha, css::color>{"4 digit hex color"}
                                   = shorthand_hex >> shorthand_hex >> shorthand_hex >> shorthand_hex;
  const auto color_short_hex = x3::rule<struct short_hex, css::color>{"3 digit hex color"}
                             = shorthand_hex >> shorthand_hex >> shorthand_hex >> x3::attr(255);

  // functional specifications
  const auto color_rgb = x3::rule<struct rgb, css::color>{"rgb"}
                       = (x3::lit("rgb") >> '(' >> percentage_or_uint8_as_float >> ',' >> percentage_or_uint8_as_float >> ',' >> percentage_or_uint8_as_float >> ')')
                          [factory(&css::color::rgbf)];
  const auto color_rgba = x3::rule<struct rgba, css::color>{"rgba"}
                        = (x3::lit("rgba") >> '(' >> percentage_or_uint8_as_float >> ',' >> percentage_or_uint8_as_float >> ',' >> percentage_or_uint8_as_float >> ',' >> percentage_or_normalized >> ')')
                           [factory(&css::color::rgbaf)];
  const auto color_hsl = x3::rule<struct hsl, css::color>{"hsl"}
                       = (x3::lit("hsl") >> '(' >> degrees_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ')')
                          [factory(&css::color::hsl)];
  const auto color_hsla = x3::rule<struct hsla, css::color>{"hsla"}
                        = (x3::lit("hsla") >> '(' >> degrees_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ')')
                           [factory(&css::color::hsla)];

  const auto color = x3::rule<struct color_, css::color>{"color"}
                   = named_color
                   | x3::lexeme['#' >> ( color_hex_alpha
                                       | color_hex
                                       | color_short_hex_alpha
                                       | color_short_hex
                                       )]
                   | color_rgb
                   | color_rgba
                   | color_hsl
                   | color_hsla
                   ;
}

#endif
