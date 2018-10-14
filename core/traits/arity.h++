/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2018 Ruben Van Boxem
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
 * Arity
 * Determines the number of arguments of a callable object.
 * For obvious reasons, this does not work on overloaded functions, function templates and polymorphic lambdas.
 */

#ifndef SKUI_CORE_TRAITS_ARITY_H
#define SKUI_CORE_TRAITS_ARITY_H

#include <type_traits>

namespace skui::core
{
  template<typename... ArgTypes>
  struct count : std::integral_constant<std::size_t, sizeof...(ArgTypes)> {};

  // Most functors - defer to plain member function case
  template<typename T>
  struct arity : arity<decltype(&std::remove_reference_t<T>::operator())> {};

  // Plain function pointers
  template<typename ReturnType, typename... ArgTypes>
  struct arity<ReturnType(*)(ArgTypes...)> : count<ArgTypes...> {};

  // Member function pointers
  template<typename ClassType, typename ReturnType, typename... ArgTypes>
  struct arity<ReturnType(ClassType::*)(ArgTypes...)> : count<ArgTypes...> {};

  // Const member function pointers
  template<typename ClassType, typename ReturnType, typename... ArgTypes>
  struct arity<ReturnType(ClassType::*)(ArgTypes...) const> : count<ArgTypes...> {};

  // Value alias
  template<typename... ArgTypes>
  constexpr std::size_t arity_v = arity<ArgTypes...>::value;
}

#endif
