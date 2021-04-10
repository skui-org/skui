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
 * core::proxy_map
 * An associative proxy interface to an underlying map-like data collection.
 * It is not iterabe because not all associative collections are iterable.
 * It return a proxy_value object that can be assigned to and converts to the underlying value for its key.
 */

#ifndef SKUI_CORE_PROXY_MAP_H
#define SKUI_CORE_PROXY_MAP_H

#include <functional>
#include <ostream>
#include <type_traits>

namespace skui::core
{
  template<typename KeyType, typename ValueType>
  class proxy_map;

  template<typename KeyType, typename ValueType>
  class proxy_value
  {
  public:
    using key_type = std::add_const_t<KeyType>;
    using value_type = ValueType;
    using setter_type = std::function<void(const KeyType&, ValueType)>;
    using getter_type = std::function<ValueType(const KeyType&)>;

    proxy_value& operator=(const value_type& new_value)
    {
      set(key, new_value);
      return *this;
    }

    operator value_type() const
    {
      return get(key);
    }

    bool operator==(const value_type& value) const { return static_cast<const value_type&>(*this) == value; }
    bool operator!=(const value_type& value) const { return static_cast<const value_type&>(*this) != value; }
    bool operator< (const value_type& value) const { return static_cast<const value_type&>(*this) <  value; }
    bool operator<=(const value_type& value) const { return static_cast<const value_type&>(*this) <= value; }
    bool operator> (const value_type& value) const { return static_cast<const value_type&>(*this) >  value; }
    bool operator>=(const value_type& value) const { return static_cast<const value_type&>(*this) >= value; }

  private:
    friend class proxy_map<KeyType, ValueType>;
    proxy_value(key_type key,
                const getter_type& getter,
                const setter_type& setter)
      : key{std::move(key)}
      , get{getter}
      , set{setter}
    {}

    const key_type key;
    const getter_type& get;
    const setter_type& set;
  };

  template<typename KeyType, typename ValueType>
  class proxy_map
  {
  public:
    using proxy_value_type = proxy_value<KeyType, ValueType>;
    using key_type = typename proxy_value_type::key_type;
    using value_type = typename proxy_value_type::value_type;
    using getter_type = typename proxy_value_type::getter_type;
    using setter_type = typename proxy_value_type::setter_type;

    template<typename Getter, typename Setter>
    proxy_map(Getter getter, Setter setter)
      : get{std::move(getter)}
      , set{std::move(setter)}
    {}

    proxy_value_type operator[](const key_type& key) const
    {
      return {key, get, set};
    }

    void insert(const key_type& key, value_type value)
    {
      set(key, std::move(value));
    }

  private:
    const getter_type get;
    const setter_type set;
  };

  template<typename KeyType, typename ValueType>
  std::ostream& operator<<(std::ostream& os, const proxy_value<KeyType, ValueType>& value)
  {
    return os << static_cast<const ValueType&>(value);
  }
}

#endif
