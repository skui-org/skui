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

#ifndef SKUI_CORE_OVERLOAD_H
#define SKUI_CORE_OVERLOAD_H

namespace skui::core
{
  namespace detail
  {
    template<typename... ArgTypes>
    struct overload
    {
      template<typename ReturnType>
      constexpr auto operator()(ReturnType(*function_pointer)(ArgTypes...)) const
      {
        return function_pointer;
      }
      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* member_function_pointer)(ArgTypes...)) const
      {
        return member_function_pointer;
      }

      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* const_member_function_pointer)(ArgTypes...) const) const
      {
        return const_member_function_pointer;
      }

      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* volatile_member_function_pointer)(ArgTypes...) volatile) const
      {
        return volatile_member_function_pointer;
      }

      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* const_volatile_member_function_pointer)(ArgTypes...) const volatile) const
      {
        return const_volatile_member_function_pointer;
      }
    };
  }
  template<typename... ArgTypes>
  constexpr detail::overload<ArgTypes...> overload{};
}

#endif
