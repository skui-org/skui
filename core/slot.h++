/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

#include "core/traits/arity.h++"

namespace skui::core
{
  template<typename ReturnType, typename... ArgTypes>
  class slot
  {
  public:
    // Callable
    template<typename CallableType>
    slot(CallableType&& callable)
      : target{nullptr}
      , proxy{bind(std::forward<CallableType>(callable))}
    {}
    // Member function
    template<typename ClassType,
             typename FunctionClassType,
             typename FunctionReturnType,
             typename... FunctionArgTypes,
             typename = std::enable_if_t<!std::is_const_v<ClassType>>>
    slot(ClassType* instance,
         FunctionReturnType (FunctionClassType::* member_function_pointer)(FunctionArgTypes...))
      : target{get_pointer_to_most_derived(instance)}
      , proxy{bind(instance, member_function_pointer)}
    {
      static_assert(std::is_base_of<FunctionClassType, ClassType>::value,
                    "You can only wrap member functions of a related object.");
    }
    // Const member function
    template<typename ClassType,
             typename FunctionClassType,
             typename FunctionReturnType,
             typename... FunctionArgTypes>
    slot(const ClassType* instance,
         FunctionReturnType (FunctionClassType::* const_member_function_pointer)(FunctionArgTypes...) const)
      : target{get_pointer_to_most_derived(instance)}
      , proxy{bind(instance, const_member_function_pointer)}
    {
      static_assert(std::is_base_of<FunctionClassType, ClassType>::value,
                    "You can only wrap member functions of a related object.");
    }

    slot(const slot& other) = default;
    slot(slot&& other)
      : target{other.target}
      , proxy{std::move(other.proxy)}
    {
      other.object = nullptr;
    }

    template<typename... InputArgTypes>
    auto operator()(InputArgTypes&&... input_arguments) const
    {
      return proxy(target, std::forward<InputArgTypes>(input_arguments)...);
    }

    void reseat(const void* object)
    {
      target = object;
    }

    template<typename T>
    const T* get_target() const
    {
      return static_cast<T*>(target);
    }

  private:
    const void* target;
    std::function<ReturnType(const void*, ArgTypes...)> proxy;

    // Pointer to most derived class in inheritance chain
    template<typename ClassType>
    static auto get_pointer_to_most_derived(ClassType* instance)
    {
      if constexpr(std::is_polymorphic_v<ClassType>)
        return dynamic_cast<const void*>(instance);
      else
        return instance;
    }

    // binding all types of callable objects in a lambda
    template<typename CallableType>
    auto bind(CallableType&& callable)
    {
      return [callable = std::move(callable)](const void*, auto&&... arguments)
             {
               return call(callable,
                           std::make_index_sequence<arity_v<CallableType>>(),
                           std::forward<ArgTypes>(arguments)...);
             };
    }
    template<typename ClassType,
             typename FunctionClassType,
             typename FunctionReturnType,
             typename... FunctionArgTypes>
    auto bind(ClassType*,
              FunctionReturnType(FunctionClassType::* member_function_pointer)(FunctionArgTypes...))
    {
      return [=] (const void* object, auto&&... arguments)
             {
               return call(member_function_pointer,
                           std::make_index_sequence<sizeof...(FunctionArgTypes)>(),
                           const_cast<ClassType*>(static_cast<const ClassType*>(object)),
                           std::forward<decltype(arguments)>(arguments)...);
             };
    }
    template<typename ClassType,
             typename FunctionClassType,
             typename FunctionReturnType,
             typename... FunctionArgTypes>
    auto bind(const ClassType*,
              FunctionReturnType(FunctionClassType::* const_member_function_pointer)(FunctionArgTypes...) const)
    {
      return [=] (const void* object, auto&&... arguments)
             {
               return call(const_member_function_pointer,
                           std::make_index_sequence<sizeof...(FunctionArgTypes)>(),
                           static_cast<const ClassType*>(object),
                           std::forward<decltype(arguments)>(arguments)...);
             };
    }


    // arity matching - drop extra arguments to slot function
    template<typename CallableType, std::size_t... Indices>
    static ReturnType call(CallableType&& callable,
                           const std::index_sequence<Indices...>&,
                           ArgTypes... args)
    {
      return callable(std::get<Indices>(std::make_tuple(args...))...);
    }

    template<typename MemberFunctionPointer, typename ClassType, std::size_t ... Indices>
    static ReturnType call(MemberFunctionPointer member_function_pointer,
                           const std::index_sequence<Indices...>&,
                           ClassType* object,
                           ArgTypes&&... args)
    {
      return (object->*member_function_pointer)(std::get<Indices>(std::make_tuple(args...))...);
    }
  };
}

#endif
