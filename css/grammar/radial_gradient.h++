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

#ifndef SKUI_CSS_GRAMMAR_RADIAL_GRADIENT_H
#define SKUI_CSS_GRAMMAR_RADIAL_GRADIENT_H

#include "css/grammar/as.h++"
#include "css/grammar/color_stop.h++"
#include "css/grammar/repeating.h++"
#include "css/grammar/length.h++"
#include "css/grammar/position.h++"
#include "css/grammar/x3_stdvariant.h++"

#include "css/property/radial_gradient.h++"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::radial_gradient,
                          repeating, shape, position, colors)
BOOST_FUSION_ADAPT_STRUCT(skui::css::radial_gradient::circle,
                          radius)
BOOST_FUSION_ADAPT_STRUCT(skui::graphics::size2D<skui::css::length>,
                          width, height)
BOOST_FUSION_ADAPT_STRUCT(skui::css::radial_gradient::ellipse,
                          size)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  struct radial_gradient_extent_table : x3::symbols<css::radial_gradient::extent>
  {
    radial_gradient_extent_table();
  } const radial_gradient_extent;

  const auto circle = x3::rule<struct circle, css::radial_gradient::circle>{"circle"}
                    = x3::lit("circle") >> -( length
                                            | radial_gradient_extent
                                            );

  const auto ellipse = x3::rule<struct ellipse, css::radial_gradient::ellipse>{"ellipse"}
                     = x3::lit("ellipse") >> -( length_percentage >> length_percentage
                                              | radial_gradient_extent
                                              );

  const auto position_or_center = ( "at" >> position
                                  | x3::attr(css::center)
                                  );

  const auto radial_gradient = x3::rule<struct radial_gradient, css::radial_gradient>{"radial-gradient"}
                             = repeating >> x3::lit("radial-gradient")
                               >> '(' >> !x3::lit(',') >> -( -( circle
                                                              | ellipse
                                                              ) >> position_or_center >> x3::lit(',')
                                                           )
                                      >> color_stop % ','
                               >> ')';
}

#endif
