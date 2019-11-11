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

/*
 * css::grammar::background
 * Rule to parse composite CSS background property.
 */

#ifndef SKUI_CSS_GRAMMAR_BACKGROUND_H
#define SKUI_CSS_GRAMMAR_BACKGROUND_H

#include "css/grammar/color.h++"
#include "css/grammar/conic_gradient.h++"
#include "css/grammar/linear_gradient.h++"
#include "css/grammar/make_property.h++"
#include "css/grammar/property_symbols_table.h++"
#include "css/grammar/radial_gradient.h++"
#include "css/grammar/url.h++"
#include "css/grammar/x3_stdvariant.h++"

#include "css/property/background.h++"

#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::background_size_width_height,
                          width, height)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  struct background_repeat_table : property_symbols_table<css::background_repeat>
  {
    background_repeat_table();
  } const background_repeat;
  struct background_origin_table : property_symbols_table<css::background_origin>
  {
    background_origin_table();
  } const background_origin;
  struct background_clip_table : property_symbols_table<css::background_clip>
  {
    background_clip_table();
  } const background_clip;
  struct background_attachment_table : property_symbols_table<css::background_attachment>
  {
    background_attachment_table();
  } const background_attachment;
  struct background_size_keyword_table : x3::symbols<css::background_size_keyword>
  {
    background_size_keyword_table();
  } const background_size_keyword;

  const auto background_image = x3::rule<struct background_image_, css::background_image>{"background-image"}
                              = ( x3::lit("none") >> x3::attr(core::string{})
                                | url
                                | conic_gradient
                                | linear_gradient
                                | radial_gradient
                                ) % ',';
  const auto background_position = x3::rule<struct background_position_, std::vector<css::position>>{"background-position"}
                                 = position % ',';

  const auto length_or_auto = ( length_percentage
                              | "auto" >> x3::attr(css::background_size_auto)
                              );
  const auto background_size_width_height = x3::rule<struct background_size_width_height, css::background_size_width_height>{"background-size-width-height"}
                                          = length_or_auto >> ( length_or_auto | x3::attr(css::background_size_auto) );

  const auto background_size = x3::rule<struct background_size_, css::background_size>{"background-size"}
                             = ( background_size_keyword
                               | background_size_width_height
                               ) % ',';


  const auto background = x3::rule<struct background, css::background>{"background"}
                        = -color >> -background_image >> -background_position >> -background_size;
}

#endif
