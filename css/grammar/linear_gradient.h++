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

#ifndef SKUI_CSS_GRAMMAR_LINEAR_GRADIENT_H
#define SKUI_CSS_GRAMMAR_LINEAR_GRADIENT_H

#include "css/grammar/angle.h++"
#include "css/grammar/color_stop.h++"
#include "css/grammar/repeating.h++"

#include "css/property/linear_gradient.h++"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::linear_gradient,
                          repeating, direction, colors)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  struct linear_gradient_direction_table : x3::symbols<css::position>
  {
    linear_gradient_direction_table();
  } const linear_gradient_direction;

  const auto direction_or_angle = x3::rule<struct direction_or_angle, std::variant<css::position, css::angle>>{"direction-or-angle"}
                                = ( "to" >> linear_gradient_direction
                                  | angle
                                  );

  const auto linear_gradient = x3::rule<struct linear_gradient, css::linear_gradient>{"linear-gradient"}
                             = repeating
                               >> x3::lit("linear-gradient") >> "(" >> ( direction_or_angle >> ','
                                                                       | x3::attr(css::top)
                                                                       )
                                                                    >> color_stop % ','
                                                             >> ")";
}

#endif
