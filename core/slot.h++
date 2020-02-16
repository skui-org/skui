/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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
 * Slot
 * Wrapper for functions connected to slots.
 * This provides a uniform interface across all callables for e.g. signals.
 */

#ifndef SKUI_CORE_SLOT_H
#define SKUI_CORE_SLOT_H

#include <functional>
#include <utility>

#include "core/traits/arity.h++"

namespace skui::core::implementation
{
  // interface
  template<typename ReturnType, typename... ArgTypes>
  class slot
  {
  public:
    virtual ~slot() = default;

    virtual ReturnType operator()(const void* object, ArgTypes...) const = 0;

  protected:
    slot() = default;
  };

  // Implementation for function pointers and functors (including lambdas)
  template<typename Callable, typename ReturnType = void, typename... ArgTypes>
  class callable_slot : public slot<ReturnType, ArgTypes...>
  {
  public:
    callable_slot(Callable function_pointer_or_lambda)
      : callable{function_pointer_or_lambda}
    {}

    ReturnType operator()(const void*, ArgTypes... args) const override
    {
      return call(std::make_index_sequence<arity_v<Callable>>{},
                  std::forward<ArgTypes>(args)...);
    }

  private:
    template<std::size_t... Indices>
    ReturnType call(const std::index_sequence<Indices...>&,
                    ArgTypes&&... args) const
    {
      ((void)args, ...);

      return callable(std::get<Indices>(std::make_tuple(args...))...);
    }

    Callable callable;
  };

  // Implementation for member functions
  template<typename Class, typename MemberFunctionPointer, typename ReturnType, typename... ArgTypes>
  class member_function_slot : public slot<ReturnType, ArgTypes...>
  {
  public:
    member_function_slot(MemberFunctionPointer member_function)
      : member_function_ptr{member_function}
    {}

    ReturnType operator()(const void* object, ArgTypes... args) const override
    {
      return call(std::make_index_sequence<arity_v<MemberFunctionPointer>>{},
                  const_cast<Class*>(static_cast<const Class*>(object)),
                  std::forward<ArgTypes>(args)...);
    }

  private:
    template<std::size_t ... Indices>
    ReturnType call(const std::index_sequence<Indices...>&,
                    Class* object,
                    ArgTypes&&... args) const
    {
      ((void)args, ...);

      return (object->*member_function_ptr)(std::get<Indices>(std::make_tuple(args...))...);
    }

    MemberFunctionPointer member_function_ptr;
  };

  // Implementation for const member functions
  template<typename Class, typename ConstMemberFunctionPointer, typename ReturnType, typename... ArgTypes>
  class const_member_function_slot : public slot<ReturnType, ArgTypes...>
  {
  public:
    const_member_function_slot(ConstMemberFunctionPointer const_member_function)
      : const_member_function_ptr{const_member_function}
    {}

    ReturnType operator()(const void* object, ArgTypes... args) const override
    {
      return call(std::make_index_sequence<arity_v<ConstMemberFunctionPointer>>{},
                  static_cast<const Class*>(object),
                  std::forward<ArgTypes>(args)...);
    }

  private:
    template<std::size_t... Indices>
    ReturnType call(const std::index_sequence<Indices...>&,
                    const Class* object,
                    ArgTypes&&... args) const
    {
      ((void)args, ...);

      return (object->*const_member_function_ptr)(std::get<Indices>(std::make_tuple(args...))...);
    }

    ConstMemberFunctionPointer const_member_function_ptr;
  };
}

#endif
