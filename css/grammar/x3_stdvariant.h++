/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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
 * Boost.Spirit.X3 std::variant compatibility
 * See https://github.com/boostorg/spirit/issues/270#issuecomment-439160933.
 * This is incomplete, yet enables the enough functionality for its uses here.
 */

#ifndef SKUI_CSS_GRAMMAR_X3_STDVARIANT_H
#define SKUI_CSS_GRAMMAR_X3_STDVARIANT_H

#include <variant>

#include <boost/mpl/vector.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/variant_find_substitute.hpp>
#include <boost/spirit/home/x3/support/traits/variant_has_substitute.hpp>

// Based on: boost/spirit/home/x3/support/traits/variant_find_substitute.hpp
namespace boost::spirit::x3::traits
{
  template<typename... Ts> struct is_variant<std::variant<Ts...>> : mpl::true_ {};

  template<typename... Ts, typename Attribute>
  struct variant_find_substitute<std::variant<Ts...>, Attribute>
  {
    using variant_type = std::variant<Ts...>;
    using types = mpl::vector<Ts...>;
    using end = typename mpl::end<types>::type;

    using iter_1 = typename mpl::find_if<types, is_same<mpl::_1, Attribute>>::type;

    using iter = typename mpl::eval_if<is_same<iter_1, end>,
                                       mpl::find_if<types, traits::is_substitute<mpl::_1, Attribute>>,
                                       mpl::identity<iter_1>>::type;

    using type = typename mpl::eval_if<is_same<iter, end>,
                                       mpl::identity<Attribute>,
                                       mpl::deref<iter>>::type;
  };

  template<typename... Ts>
  struct variant_find_substitute<std::variant<Ts...>, std::variant<Ts...>> : mpl::identity<std::variant<Ts...>> {};

  template<typename... Ts, typename Attribute>
  struct variant_has_substitute_impl<std::variant<Ts...>, Attribute>
  {
    // Find a type from the variant that can be a substitute for Attribute.
    // return true_ if one is found, else false_

    using types = mpl::vector<Ts...>;

    using end = typename mpl::end<types>::type;

    using iter_1 = typename mpl::find_if<types, is_same<mpl::_1, Attribute>>::type;

    using iter = typename mpl::eval_if<is_same<iter_1, end>,
                                       mpl::find_if<types, traits::is_substitute<mpl::_1, Attribute>>,
                                       mpl::identity<iter_1>>::type;

    using type = mpl::not_<is_same<iter, end>>;
  };

  template<typename Out, typename... Ts>
  void print_attribute(Out& out, const std::variant<Ts...>& variant)
  {
    std::visit([&out](const auto& value) { out << value; }, variant);
  }
}

#endif
