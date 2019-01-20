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

#ifndef SKUI_CSS_GRAMMAR_SEMANTIC_FACTORY_H
#define SKUI_CSS_GRAMMAR_SEMANTIC_FACTORY_H

#include <boost/fusion/include/size.hpp>
#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  using namespace boost::spirit::x3;

  namespace implementation
  {
    template<typename Functor, typename Sequence, std::size_t... Indices>
    constexpr decltype(auto) apply(Functor functor, Sequence sequence, std::index_sequence<Indices...>)
    {
      return std::invoke(std::forward<Functor>(functor), boost::fusion::at_c<Indices>(std::forward<Sequence>(sequence))...);
    }
  }

  template<typename Functor, typename Sequence>
  constexpr decltype(auto) apply(Functor functor, Sequence sequence)
  {
    return implementation::apply(std::forward<Functor>(functor),
                                 std::forward<Sequence>(sequence),
                                 std::make_index_sequence<size(sequence)>{});
  }
  template<typename Functor>
  auto factory(Functor f)
  {
    return [f](auto& ctx)
           {
             _val(ctx) = apply(f, _attr(ctx));
           };
  }
}

#endif
