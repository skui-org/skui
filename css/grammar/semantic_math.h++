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

#ifndef SKUI_CSS_GRAMMAR_SEMANTIC_MATH_H
#define SKUI_CSS_GRAMMAR_SEMANTIC_MATH_H

#include <boost/spirit/home/x3.hpp>

#include <type_traits>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  template<typename ValueType>
  struct divide
  {
    constexpr divide(ValueType value) : divisor{value} {}

    template<typename ContextType>
    void operator()(ContextType& context) const
    {
      // triggers conversion warnings when multiplying integer types with sizeof(T) < sizeof(int)
      using attribute_type = std::remove_reference_t<decltype(x3::_attr(context))>;
      x3::_attr(context) = static_cast<attribute_type>(x3::_attr(context) / divisor);
    }

  private:
    const ValueType divisor;
  };

  template<typename ValueType>
  struct multiply
  {
    constexpr multiply(ValueType value) : factor{value} {}

    template<typename ContextType>
    void operator()(ContextType& context) const
    {
      // triggers conversion warnings when multiplying integer types with sizeof(T) < sizeof(int)
      using attribute_type = std::remove_reference_t<decltype(x3::_attr(context))>;
      x3::_attr(context) = static_cast<attribute_type>(x3::_attr(context) * factor);
    }

  private:
    const ValueType factor;
  };
  template<typename ValueType>
  struct clamp
  {
    constexpr clamp(ValueType max) : lower{0}, upper{max} {}
    constexpr clamp(ValueType min, ValueType max) : lower{min}, upper{max} {}

    template<typename ContextType>
    void operator()(ContextType& context)
    {
      using value_type = std::remove_reference_t<decltype(x3::_val(context))>;
      x3::_val(context) = std::clamp<value_type>(x3::_attr(context), lower, upper);
    }

  private:
    const ValueType lower;
    const ValueType upper;
  };

  constexpr auto round = [](auto& context)
  {
    using value_type = std::remove_reference_t<decltype(x3::_val(context))>;
    x3::_val(context) = static_cast<value_type>(std::round(x3::_attr(context)));
  };
}

#endif
