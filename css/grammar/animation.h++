/**
 * The MIT License (MIT)
 *
 * Copyright © 2019-2020 Ruben Van Boxem
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

#ifndef SKUI_CSS_GRAMMAR_ANIMATION_H
#define SKUI_CSS_GRAMMAR_ANIMATION_H

#include "css/grammar/property_symbols_table.h++"
#include "css/grammar/time.h++"
#include "css/grammar/timing_function.h++"
#include "css/grammar/x3_stdvariant.h++"

#include "css/property/animation.h++"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::animation,
                          name,
                          duration,
                          timing_function,
                          delay,
                          iteration_count,
                          direction,
                          fill_mode,
                          play_state)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto animation_name = x3::rule<struct name, core::string>{"animation-name"}
                            = x3::lexeme[x3::alpha >> *(x3::char_ - x3::space)];

  const auto animation_duration = x3::rule<struct duration, css::time>{"animation-duration"}
                                = time;

  const auto animation_timing_function = x3::rule<struct animation_timing_function, css::timing_function>{"animation-timing-function"}
                                       = timing_function;

  const auto animation_delay = x3::rule<struct delay, css::time>{"animation-delay"}
                             = time;

  const auto animation_iteration_count = x3::rule<struct animation_iteration_count, css::property<std::uint64_t, css::infinite_t>>{"animation-iteration-count"}
                                       = x3::uint_
                                       | "infinite" >> x3::attr(infinite);

  struct direction_table : property_symbols_table<css::animation_direction>
  {
    direction_table();
  } const animation_direction;

  struct fill_mode_table : property_symbols_table<css::fill_mode>
  {
    fill_mode_table();
  } const animation_fill_mode;

  struct play_state_table : property_symbols_table<css::play_state>
  {
    play_state_table();
  } const animation_play_state;

  const auto animation = x3::rule<struct animation, css::animation>{"animation"}
                       = x3::lit("inherit") >> x3::attr(css::animation{css::inherit})
                       | -animation_name >> -animation_duration
                               >> -animation_timing_function
                               >> -animation_delay
                               >> -animation_iteration_count
                               >> -animation_direction
                               >> -animation_fill_mode
                               >> -animation_play_state;
}

#endif
