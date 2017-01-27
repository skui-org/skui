/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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
 * value_ptr
 * "deep_copy_ptr": a std::unique_ptr with additional copy semantics.
 * Necessary so that a smart_ptr to base can be copied without slicing.
 * Design notes:
 *  - not as robust as std::unique_ptr
 *  - does not work with arrays currently
 *  - missing some C++11 fluff (noexcept, constexpr, etc.)
 */

#ifndef SKUI_CORE_VALUE_PTR_H
#define SKUI_CORE_VALUE_PTR_H

#include <memory>
#include <tuple>
#include <type_traits>

namespace skui
{
  namespace core
  {
    template <typename T>
    static void* (*copy_constructor_copier())(void*)
    {
      return [](void* other)
             { return static_cast<void*>(new T(*static_cast<T*>(other))); };
    }

    template<typename T>
    class smart_copy
    {
    public:
      using copy_function_type = void*(*)(void*);

      explicit smart_copy() { static_assert(!std::is_abstract<T>::value, "Cannot default construct smart_copy for an abstract type."); }
      explicit smart_copy(copy_function_type copy_function) : copy_function(copy_function) {}
      smart_copy(const smart_copy& other) : copy_function(other.get_copy_function()) {}
      template<typename U>
      smart_copy(const smart_copy<U>& other) : copy_function(other.get_copy_function()) {}

      void* operator()(void* other) const { return copy_function(other); }
      copy_function_type get_copy_function() const { return copy_function; }

    private:
      copy_function_type copy_function = copy_constructor_copier<T>();
    };

    template<typename T,
             typename Copier = smart_copy<T>,
             typename Deleter = std::default_delete<T>>
    class value_ptr
    {
      using pointer = std::add_pointer_t<T>;
      using element_type = std::remove_reference_t<T>;
      using reference = std::add_lvalue_reference_t<element_type>;
      using const_reference = std::add_const_t<reference>;
      using copier_type = Copier;
      using deleter_type = Deleter;

    public:
      explicit constexpr value_ptr() = default;
      explicit constexpr value_ptr(std::nullptr_t) : value_ptr() {}
      explicit value_ptr(pointer p) : data{p, copier_type(), deleter_type()} {}

      ~value_ptr()
      {
        reset(nullptr);
      }

      explicit value_ptr(const value_ptr& other)
        : data{static_cast<pointer>(other.get_copier()(other.get())), other.get_copier(), other.get_deleter()} {}
      explicit value_ptr(value_ptr&& other)
        : data{other.get(), other.get_copier(), other.get_deleter()} { other.release(); }
      template<typename U, typename OtherCopier>
      value_ptr(const value_ptr<U, OtherCopier>& other)
        : data{static_cast<pointer>(other.get_copier().get_copy_function()(other.get())), other.get_copier(), other.get_deleter()} {}
      template<typename U, typename OtherCopier>
      value_ptr(value_ptr<U, OtherCopier>&& other)
        : data{other.get(), other.get_copier(), other.get_deleter()} { other.release(); }

      const value_ptr& operator=(value_ptr other) { swap(data, other.data); return *this; }
      template<typename U, typename OtherCopier, typename OtherDeleter>
      value_ptr& operator=(value_ptr<U, OtherCopier, OtherDeleter> other) { std::swap(data, other.data); return *this; }

      pointer operator->() { return get(); }
      const pointer operator->() const { return get(); }

      reference operator*() { return *get(); }
      const_reference operator*() const { return *get(); }

      pointer get() { return std::get<0>(data); }
      const pointer get() const { return std::get<0>(data); }

      copier_type& get_copier() { return std::get<1>(data); }
      const copier_type& get_copier() const { return std::get<1>(data); }
      deleter_type& get_deleter() { return std::get<2>(data); }
      const deleter_type& get_deleter() const { return std::get<2>(data); }

      void reset(pointer new_data)
      {
        if(get())
        {
          get_deleter()(get());
        }
        std::get<0>(data) = new_data;
      }

      pointer release() noexcept
      {
        pointer result = get();
        std::get<0>(data) = pointer();
        return result;
      }

    private:
      std::tuple<pointer, copier_type, deleter_type> data = {nullptr, smart_copy<T>(), std::default_delete<T>()};
    };

    template<typename T, typename... ArgTypes>
    value_ptr<T> make_value(ArgTypes&&... args)
    {
      return value_ptr<T>(new T(std::forward<ArgTypes>(args)...));;
    }
  }
}

#endif
