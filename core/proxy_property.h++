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
 * Proxy Property
 * Property that wraps an external resource.
 * Note: the changed signal is only emitted when the value is changed through
 *       the proxy_property/
 */

#ifndef SKUI_CORE_PROXY_PROPERTY_H
#define SKUI_CORE_PROXY_PROPERTY_H

#include "signal.h++"

#include <functional>

namespace skui
{
  namespace core
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
        : set(setter)
        , get(getter)
      {
        set(value);
      }
      template<typename Setter, typename Getter>
      proxy_property(Setter setter, Getter getter)
        : set(setter)
        , get(getter)
      {}
      proxy_property(const proxy_property& other) = default;
      proxy_property(proxy_property&&) = default;

      proxy_property& operator=(proxy_property other)
      {
        std::swap(other.set, set);
        std::swap(other.get, get);

        value_type current_value = get();
        if(current_value != other.get())
          value_changed.emit(current_value);

        return *this;
      }

      proxy_property& operator=(const_reference& other)
      {
        const bool changed = other != get();
        set(other);
        if(changed)
          value_changed.emit(other);

        return *this;
      }

      operator value_type() const { return get(); }

      bool operator==(const_reference other) const { return get() == other; }
      bool operator!=(const_reference other) const { return get() != other; }
      bool operator< (const_reference other) const { return get() <  other; }
      bool operator<=(const_reference other) const { return get() <= other; }
      bool operator> (const_reference other) const { return get() >  other; }
      bool operator>=(const_reference other) const { return get() >= other; }

      signal<value_type> value_changed;

    private:
      std::function<void(const T&)> set;
      std::function<T()> get;
    };
  }
}

#endif
