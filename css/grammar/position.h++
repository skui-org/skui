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

#ifndef SKUI_CSS_GRAMMAR_POSITION_H
#define SKUI_CSS_GRAMMAR_POSITION_H

#include "css/length.h++"
#include "css/position.h++"

#include "css/grammar/as.h++"
#include "css/grammar/length.h++"

#include <core/debug.h++>

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/adapted/struct/adapt_struct_named.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::position,
                          x,
                          y)
BOOST_FUSION_ADAPT_STRUCT(skui::css::length_with_offset,
                          value,
                          offset)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  constexpr auto swap_x_y = [](auto& context)
  {
    css::position& position = x3::_attr(context);

    std::swap(position.x, position.y);
  };

  struct horizontal_relative_position_table : x3::symbols<css::length>
  {
    horizontal_relative_position_table();
  } const horizontal_relative_position;

  struct vertical_relative_position_table : x3::symbols<css::length>
  {
    vertical_relative_position_table();
  } const vertical_relative_position;

  const auto horizontal_position = x3::rule<struct horizontal_position, css::length_with_offset>{"horizontal_position"}
                                                    = horizontal_relative_position >> -length_percentage
                                                    | length_percentage >> x3::attr(css::length{})
                                                    ;
  const auto vertical_position = x3::rule<struct vertical_position, css::length_with_offset>{"vertical_position"}
                                                    = vertical_relative_position >> -length_percentage
                                                    | length_percentage >> x3::attr(css::length{})
                                                    ;

  //| vertical_relative_position
  const auto position = x3::rule<struct position_, css::position>{"position"}
                     %= horizontal_position >> vertical_position
                      | (vertical_position >> horizontal_position)[swap_x_y]
                      | horizontal_position >> x3::attr(css::length_with_offset{{50, unit::percentage}, {}})
                      | (vertical_position >> x3::attr(css::length_with_offset{{50, unit::percentage}, {}}))[swap_x_y]
                      ;
}
#endif
