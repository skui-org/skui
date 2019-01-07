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

#include "css/declaration_block.h++"

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  using boost::spirit::x3::lexeme;
  using boost::spirit::x3::traits::move_to;

  //struct tracking_tag {};

  template<typename Context, typename... PointerToMemberTypes>
  auto& member_ref(Context& context, PointerToMemberTypes... member)
  {
    return (_val(context).* ... .* member);
  }

  template<typename PropertyType, typename ValueType, typename... PointerToMemberTypes>
  auto make_property(const PropertyType& property, const ValueType& value, PointerToMemberTypes... member)
  {
    const auto setter = [member...](auto& context)
    {
      //get<tracking_tag>(context).get().insert(std::addressof(_val(context).* ... .* member));

      move_to(_attr(context), member_ref(context, member...));
    };
    return lexeme[property] >> ':' >> value[setter] >> ';';
  }

  template<typename PropertyType, typename ValueType, typename... PointerToMemberType>
  auto make_background_property(const PropertyType& property, const ValueType& value, PointerToMemberType... member)
  {
    return make_property(property, value, &css::declaration_block::background, member...);
  }
}

#endif
