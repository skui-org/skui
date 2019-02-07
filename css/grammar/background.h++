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

#include "css/grammar/make_property.h++"
#include "css/grammar/property_symbols_table.h++"

#include "css/property/background.h++"

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto background_color = x3::rule<struct background_color, css::color>{"background-color"}
                              = x3::eoi;
  const auto background_image = x3::rule<struct background_image_, css::background_image>{"background-image"}
                              = x3::eoi;
  const auto background_position = x3::rule<struct background_position_, css::background_position>{"background-position"}
                                 = x3::eoi;
  const auto background_size = x3::rule<struct background_size_, css::background_size>{"background-size"}
                             = x3::eoi;
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

  const auto background = x3::rule<struct background, css::background>{"background"}
                        = x3::eoi;
}

#endif
