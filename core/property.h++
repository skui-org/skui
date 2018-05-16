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
 * Property
 * Utility class to handle automatic notification of observers when a value changes
 */

#ifndef SKUI_CORE_PROPERTY_H
#define SKUI_CORE_PROPERTY_H

#include "core/signal.h++"

#include <istream>
#include <ostream>
#include <type_traits>
#include <utility>

namespace skui
{
  namespace core
  {
    template<typename T>
    class property
    {
    public:
      using value_type = T;
      using reference = std::add_lvalue_reference_t<T>;
      using const_reference = std::add_lvalue_reference_t<std::add_const_t<T>>;
      using rvalue_reference = std::add_rvalue_reference_t<T>;

      property() = default;
      template<typename... SlotTypes>
      property(value_type value, SlotTypes&&... slots)
        : value{std::move(value)}
      {
        (value_changed.connect(std::forward<SlotTypes>(slots)), ...);
      }

      property& operator=(const_reference other)
      {
        const bool changed = value != other;
        value = other;
        if(changed)
          value_changed.emit(value);

        return *this;
      }
      const property& operator=(const_reference other) const
      {
        const bool changed = value != other;
        value = other;
        if(changed)
          value_changed.emit(value);

        return *this;
      }
      property& operator=(rvalue_reference other)
      {
        const bool changed = value != other;
        value = std::move(other);
        if(changed)
          value_changed.emit(value);

        return *this;
      }
      const property& operator=(rvalue_reference other) const
      {
        const bool changed = value != other;
        value = std::move(other);
        if(changed)
          value_changed.emit(value);

        return *this;
      }

      operator const_reference() const { return value; }
      const value_type* operator->() const
      {
        return &value;
      }

      bool operator==(const_reference other) const { return value == other; }
      bool operator!=(const_reference other) const { return value != other; }
      bool operator< (const_reference other) const { return value <  other; }
      bool operator<=(const_reference other) const { return value <= other; }
      bool operator> (const_reference other) const { return value >  other; }
      bool operator>=(const_reference other) const { return value >= other; }

      signal<const_reference> value_changed;

    private:
      // mutable because a property<non-const T> can be assigned a value
      mutable value_type value;
    };

    template<typename ValueType>
    std::ostream& operator<<(std::ostream& os, const property<ValueType>& property)
    {
      return os << static_cast<ValueType>(property);
    }
    template<typename ValueType>
    std::istream& operator>>(std::istream& os, property<ValueType>& property)
    {
      ValueType result;
      os >> result;
      if(os)
        property = std::move(result);

      return os;
    }
  }
}

#endif
