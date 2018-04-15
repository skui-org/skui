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
 * core::bounded_property
 * Value that can have minimum and maximum value.
 * It is self-consistent, and clamps assigned out-of-range values.
 */

#ifndef SKUI_CORE_BOUNDED_PROPERTY_H
#define SKUI_CORE_BOUNDED_PROPERTY_H

#include "core/property.h++"
#include "core/utility/bound.h++"

#include <limits>

namespace skui
{
  namespace core
  {
    template<typename T>
    class bounded_property
    {
    public:
      using value_type = T;
      using reference = std::add_lvalue_reference_t<T>;
      using const_reference = std::add_lvalue_reference_t<std::add_const_t<T>>;
      using rvalue_reference = std::add_rvalue_reference_t<T>;

      bounded_property(value_type initial_value = {})
        : value(initial_value)
        , minimum(std::numeric_limits<value_type>::lowest())
        , maximum(std::numeric_limits<value_type>::max())
        , value_changed(value.value_changed)
      {}
      bounded_property(const_reference initial_value,
                       const_reference initial_minimum,
                       const_reference initial_maximum)
        : value(initial_value)
        , minimum(initial_minimum)
        , maximum(initial_maximum)
        , value_changed(value.value_changed)
      {}
      bounded_property(const bounded_property& other)
        : value(other.value)
        , minimum(other.minimum)
        , maximum(other.maximum)
        , value_changed(value.value_changed)
      {}
      bounded_property(bounded_property&& other) noexcept
        : value(std::move(other.value))
        , minimum(std::move(other.minimum))
        , maximum(std::move(other.maximum))
        , value_changed(value.value_changed)
      {}

      bounded_property& operator=(bounded_property other)
      {
        using std::swap;

        swap(value, other.value);
        swap(minimum, other.minimum);
        swap(maximum, other.maximum);

        return *this;
      }

      bounded_property& operator=(const_reference other)
      {
        value = bound<value_type>{}(other, minimum, maximum);

        return *this;
      }

      const bounded_property& operator=(const_reference other) const
      {
        value = bound<value_type>{}(other, minimum, maximum);

        return *this;
      }

      operator const_reference() const { return value; }
      const value_type* operator->() const
      {
        return value.property<T>::operator->();
      }

      bool operator==(const_reference other) const { return value == other; }
      bool operator!=(const_reference other) const { return value != other; }
      bool operator< (const_reference other) const { return value <  other; }
      bool operator<=(const_reference other) const { return value <= other; }
      bool operator> (const_reference other) const { return value >  other; }
      bool operator>=(const_reference other) const { return value >= other; }

      bool fixed() const { return minimum == maximum; }

    private:
      property<T> value;

      T minimum;
      T maximum;

    public:
      // This one needs to come after the thing it references (property<T> value)
      signal<const_reference>& value_changed;
    };

    template<typename ValueType>
    std::ostream& operator<<(std::ostream& os, const bounded_property<ValueType>& property)
    {
        return os << static_cast<ValueType>(property);
    }
    template<typename ValueType>
    std::istream& operator>>(std::istream& os, bounded_property<ValueType>& property)
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
