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
  using namespace boost::spirit::x3;

  // Named colors
  struct named_color_table : public symbols<css::color>
  {
    named_color_table();
  } const named_color;

  // Hex specification
  const auto shorthand_hex = rule<struct _, std::uint8_t>{"shorthand hex digit"}
                           = uint_parser<std::uint8_t, 16, 1, 1>{}[multiply_by_17];

  const auto color_hex_alpha = rule<struct hex_alpha, css::color>{"8 digit hex color (extension)"}
                             = uint8_hex >> uint8_hex >> uint8_hex >> uint8_hex;
  const auto color_hex = rule<struct hex, css::color>{"6 digit hex color"}
                       = uint8_hex >> uint8_hex >> uint8_hex >> attr(255);
  const auto color_short_hex_alpha = rule<struct short_hex_alpha, css::color>{"4 digit hex color"}
                                   = shorthand_hex >> shorthand_hex >> shorthand_hex >> shorthand_hex;
  const auto color_short_hex = rule<struct short_hex, css::color>{"3 digit hex color"}
                             = shorthand_hex >> shorthand_hex >> shorthand_hex >> attr(255);

  // functional specifications
  const auto color_rgb = rule<struct rgb, css::color, true>{"rgb"}
                       = lit("rgb") >> '(' >> percentage_or_uint8 >> ',' >> percentage_or_uint8 >> ',' >> percentage_or_uint8 >> attr(255) >> ')';
  const auto color_rgba = rule<struct rgba, css::color, true>{"rgba"}
                        = lit("rgba") >> '(' >> percentage_or_uint8 >> ',' >> percentage_or_uint8 >> ',' >> percentage_or_uint8 >> ',' >> as<std::uint8_t>(percentage_or_normalized[multiply_by_255]) >> ')';
  const auto color_hsl = rule<struct hsl, css::color>{"hsl"}
                       = (lit("hsl") >> '(' >> degrees_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ')')[factory(&css::color::hsl)];
  const auto color_hsla = rule<struct hsla, css::color>{"hsla"}
                        = (lit("hsla") >> '(' >> degrees_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ',' >> percentage_or_normalized >> ')')[factory(&css::color::hsla)];

  const auto color = rule<struct color_, css::color>{"color"}
                   = named_color
                   | lexeme['#' >> ( color_hex_alpha
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
