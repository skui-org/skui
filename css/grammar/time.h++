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

#ifndef SKUI_CSS_GRAMMAR_TIME_H
#define SKUI_CSS_GRAMMAR_TIME_H

#include "css/grammar/semantic/convert_to.h++"
#include "css/grammar/semantic_math.h++"

#include <boost/spirit/home/x3.hpp>

#include <chrono>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  constexpr auto to_milliseconds = convert_to<std::chrono::milliseconds, std::chrono::milliseconds::rep>{};

  const auto milliseconds = x3::rule<struct milliseconds, float>{"milliseconds"}
                          = x3::float_[round] >> "ms";
  const auto seconds = x3::rule<struct seconds, float>{"seconds"}
                     = x3::float_[multiply{1000.f}][round] >> "s";

  const auto time = x3::rule<struct time_, std::chrono::milliseconds>{"time"}
                  = milliseconds[to_milliseconds]
                  | seconds[to_milliseconds];
}
#endif
