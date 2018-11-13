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

#ifndef SKUI_CSS_GRAMMAR_MAKE_PROPERTY_H
#define SKUI_CSS_GRAMMAR_MAKE_PROPERTY_H

#include <boost/spirit/home/x3/directive/lexeme.hpp>

namespace skui::css::grammar
{
  using boost::spirit::x3::lexeme;

  //struct tracking_tag {};

  auto make_property = [](const auto& property, const auto& value, auto member)
                       {
                         const auto setter = [member](auto& context)
                         {
                           //get<tracking_tag>(context).get().insert(std::addressof(_val(context).*member));
                           _val(context).*member = _attr(context);
                         };
                         return lexeme[property] >> ':' >> value[setter] >> ';';
                       };

  auto make_sub_property = [](const auto& property, const auto& value, auto member, auto submember)
                           {
                             const auto setter = [member, submember](auto& context)
                             {
                               (_val(context).*member).*submember = _attr(context);
                             };
                             return lexeme[property] >> ':' >> value[setter] >> ';';
                           };
}

#endif
