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

#ifndef SKUI_CSS_GRAMMAR_TIMING_FUNCTION_H
#define SKUI_CSS_GRAMMAR_TIMING_FUNCTION_H

#include "css/timing_function.h++"

#include "css/grammar/x3_stdvariant.h++"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(skui::css::steps,
                          intervals, change)
BOOST_FUSION_ADAPT_STRUCT(skui::css::cubic_bezier,
                          x1, y1, x2, y2)

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  struct timing_function_table : x3::symbols<css::timing_function>
  {
    timing_function_table();
  } const predefined_timing_function;

  const auto steps = x3::rule<struct steps, css::steps>{"steps"}
                   = x3::lit("steps") >> '(' >> x3::uint_ >> ','
                                             >> ( "start" >> x3::attr(skui::css::steps::start)
                                                | "end" >> x3::attr(skui::css::steps::end)
                                                ) >> ')';
  const auto cubic_bezier = x3::rule<struct cubic_bezier, css::cubic_bezier>{"cubic-bezier"}
                          = x3::lit("cubic-bezier") >> '(' >> x3::float_ >> ','
                                                           >> x3::float_ >> ','
                                                           >> x3::float_ >> ','
                                                           >> x3::float_ >> ')';
  const auto timing_function = predefined_timing_function
                             | steps
                             | cubic_bezier;
}

#endif
