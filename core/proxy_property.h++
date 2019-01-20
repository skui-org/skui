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
 * Proxy Property
 * Property that wraps an external resource.
 * Note: the changed signal is only emitted when the value is changed through
 *       the proxy_property.
 */

#ifndef SKUI_CORE_PROXY_PROPERTY_H
#define SKUI_CORE_PROXY_PROPERTY_H

#include "core/signal.h++"

#include <functional>
#include <istream>
#include <ostream>

namespace skui::core
{
  template<typename T>
  class proxy_property
  {
  public:
    using value_type = T;
    using reference = std::add_lvalue_reference_t<T>;
    using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
    using rvalue_reference = std::add_rvalue_reference_t<value_type>;

    template<typename Setter, typename Getter>
    proxy_property(const_reference value, Setter setter, Getter getter)
      : set{setter}
      , get{getter}
    {
      set(value);
    }
    template<typename Setter, typename Getter>
    proxy_property(Setter setter, Getter getter)
      : set{setter}
      , get{getter}
    {}

    proxy_property& operator=(const_reference& other)
    {
      const bool changed = other != static_cast<const_reference>(*this);
      if(set)
        set(other);
      if(changed)
        value_changed.emit(other);

      return *this;
    }

    const proxy_property& operator=(const_reference& other) const
    {
      const bool changed = other != static_cast<const_reference>(*this);
      if(set)
        set(other);
      if(changed)
        value_changed.emit(other);

      return *this;
    }

    operator value_type() const { return get ? get() : value_type{}; }

    bool operator==(const_reference other) const { return get ? get() == other : false; }
    bool operator!=(const_reference other) const { return get ? get() != other : false; }
    bool operator< (const_reference other) const { return get ? get() <  other : false; }
    bool operator<=(const_reference other) const { return get ? get() <= other : false; }
    bool operator> (const_reference other) const { return get ? get() >  other : false; }
    bool operator>=(const_reference other) const { return get ? get() >= other : false; }

    signal<value_type> value_changed;

  private:
    std::function<void(const T&)> set;
    std::function<T()> get;
  };

  template<typename T>
  std::ostream& operator<<(std::ostream& os, const proxy_property<T>& prop)
  {
    return os << static_cast<const T&>(prop);
  }
  template<typename ValueType>
  std::istream& operator>>(std::istream& os, proxy_property<ValueType>& property)
  {
    ValueType result;
    os >> result;
    if(os)
      property = std::move(result);

    return os;
  }
}

#endif
