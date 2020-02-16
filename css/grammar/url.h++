/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2020 Ruben Van Boxem
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
 * css::grammar::url
 * Parses resource urls
 *   url("somefile.jpg")
 */

#ifndef SKUI_CSS_GRAMMAR_URL_H
#define SKUI_CSS_GRAMMAR_URL_H

#include "css/grammar/quoted_string.h++"

#include <core/string.h++>

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto url = x3::rule<struct url, core::string>{"url"}
                 = x3::lit("url") >> '(' >> quoted_string >> ')';
}

#endif
