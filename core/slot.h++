/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ruben Van Boxem
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
 * All this is needed so that a member_function_slot can keep a pointer to the address of the member function it wraps.
 */

#ifndef SKUI_CORE_SLOT_H
#define SKUI_CORE_SLOT_H

#include <functional>
#include <utility>

namespace skui
{
  namespace core
  {
    namespace implementation
    {
      template<typename ReturnType, typename... ArgTypes>
      class slot
      {
      public:
        virtual ~slot() = default;

        virtual ReturnType operator()(const void* object, ArgTypes...) const = 0;

      protected:
        slot() = default;
      };

      template<typename Callable, typename ReturnType = void, typename... ArgTypes>
      class callable_slot : public slot<ReturnType, ArgTypes...>
      {
      public:
        callable_slot(Callable function_pointer_or_lambda) : callable(function_pointer_or_lambda) {}

        ReturnType operator()(const void*, ArgTypes... args) const override { return callable(args...); }

      private:
        Callable callable;
      };

      template<typename Callable, typename ReturnType>
      class callable_slot<Callable, ReturnType> : public slot<ReturnType>
      {
      public:
        callable_slot(Callable function_pointer_or_lambda) : callable(function_pointer_or_lambda) {}

        ReturnType operator()(const void*) const override { return callable(); }

      private:
        Callable callable;
      };

      template<typename Callable, typename ReturnType, typename... ArgTypes>
      using function_slot = callable_slot<Callable, ReturnType, ArgTypes...>;

      template<typename Class, typename ReturnType, typename... ArgTypes>
      class member_function_slot : public slot<ReturnType, ArgTypes...>
      {
        using member_function_pointer = ReturnType(Class::*)(ArgTypes...);

      public:
        member_function_slot(member_function_pointer member_function)
          : member_function_ptr(member_function)
        {}

        ReturnType operator()(const void* object, ArgTypes... args) const override
        {
          return (const_cast<Class*>(static_cast<const Class*>(object))->*member_function_ptr)(args...);
        }

      private:
        member_function_pointer member_function_ptr;
      };

      template<typename Class, typename ReturnType>
      class member_function_slot<Class, ReturnType> : public slot<ReturnType>
      {
        using member_function_pointer = ReturnType(Class::*)();

      public:
        member_function_slot(member_function_pointer member_function)
          : member_function_ptr(member_function)
        {}

        virtual ReturnType operator()(const void* object) const override
        {
          // Slot objects are stored as pointers to const, but the original connection was to a non-const object and member function
          return (const_cast<Class*>(static_cast<const Class*>(object))->*member_function_ptr)();
        }

      private:
        member_function_pointer member_function_ptr;
      };

      template<typename Class, typename ReturnType, typename... ArgTypes>
      class const_member_function_slot : public slot<ReturnType, ArgTypes...>
      {
        using const_member_function_pointer = ReturnType(Class::*)(ArgTypes...) const;

      public:
        const_member_function_slot(const_member_function_pointer const_member_function)
          : const_member_function_ptr(const_member_function)
        {}

        ReturnType operator()(const void* object, ArgTypes... args) const override
        {
          return (static_cast<const Class*>(object)->*const_member_function_ptr)(args...);
        }

      private:
        const_member_function_pointer const_member_function_ptr;
      };

      template<typename Class, typename ReturnType>
      class const_member_function_slot<Class, ReturnType> : public slot<ReturnType>
      {
        using const_member_function_pointer = ReturnType(Class::*)() const;

      public:
        const_member_function_slot(const_member_function_pointer const_member_function)
          : const_member_function_ptr(const_member_function)
        {}

        ReturnType operator()(const void* object) const override
        {
          return (static_cast<const Class*>(object)->*const_member_function_ptr)();
        }

      private:
        const_member_function_pointer const_member_function_ptr;
      };
    }
  }
}

#endif
