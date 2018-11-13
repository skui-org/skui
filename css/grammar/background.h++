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

/*
 * css::grammar::background
 * Rule to parse composite CSS background property.
 */

#ifndef SKUI_CSS_GRAMMAR_BACKGROUND_H
#define SKUI_CSS_GRAMMAR_BACKGROUND_H

#include "css/grammar/make_property.h++"

#include "css/property/background.h++"

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  using namespace boost::spirit::x3;

  const auto background_color = rule<struct background_color, graphics::color>{"background-color"}
                              = eoi;
  const auto background_image = rule<struct background_image_, css::background_image>{"background-image"}
                              = eoi;
  const auto background_position = rule<struct background_position_, css::background_position>{"background-position"}
                                 = eoi;
  const auto background_size = rule<struct background_size_, css::background_size>{"background-size"}
                             = eoi;
  struct background_repeat_table : symbols<css::background_repeat>
  {
    background_repeat_table();
  } const background_repeat;
  struct background_origin_table : symbols<css::background_origin>
  {
    background_origin_table();
  } const background_origin;
  struct background_clip_table : symbols<css::background_clip>
  {
    background_clip_table();
  } const background_clip;
  struct background_attachment_table : symbols<css::background_attachment>
  {
    background_attachment_table();
  } const background_attachment;

  const auto background = rule<struct background, css::background>{"background"}
                        = eoi;
}

#endif
