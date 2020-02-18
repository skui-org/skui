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

#ifndef SKUI_CSS_GRAMMAR_BOX_SHADOW_H
#define SKUI_CSS_GRAMMAR_BOX_SHADOW_H

#include "css/grammar/color.h++"
#include "css/grammar/length.h++"

#include "css/property/box_shadow.h++"

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::box_shadow,
                          inset, x_offset, y_offset, blur_radius, spread_radius, color)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto inset = x3::lit("inset") >> x3::attr(true)
                   | x3::attr(false);

  const auto box_shadow = x3::rule<struct box_shadow, css::box_shadow>{"box-shadow"}
                        = (inset >> -length >> -length >> -length >> -length >> -color);
}

#endif
