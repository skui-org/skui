/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
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

#ifndef SKUI_CSS_GRAMMAR_CONIC_GRADIENT_H
#define SKUI_CSS_GRAMMAR_CONIC_GRADIENT_H

#include "css/property/conic_gradient.h++"

#include "css/grammar/angle.h++"
#include "css/grammar/color_stop.h++"
#include "css/grammar/position.h++"
#include "css/grammar/repeating.h++"

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::conic_gradient,
                          repeating, from, position, colors)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto conic_gradient = x3::rule<struct conic_gradient, css::conic_gradient>{"conic-gradient"}
                            = repeating
                              >> x3::lit("conic-gradient")
                              >> '(' >> !x3::lit(',')
                                     >> -(    -( x3::lit("from") >> angle )
                                           >> -( x3::lit("at") >> position )
                                           >> x3::lit(',')
                                         )
                                     >> angular_color_stop % ','
                              >> ')';
}

#endif
