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
 * Property
 * Utility class to handle automatic notification of observers when a value changes
 */

#include "signal.h++"

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

      property() : value() {}

      property(const value_type& value_) : value(value_) {}

      operator reference() { return value; }
      operator const_reference() const { return value; }

      reference operator=(const_reference value_)
      {
        const bool changed = value != value_;
        if(changed)
        {
          value = value_;
          value_changed.emit();
        }
      }

      void operator=(rvalue_reference value_)
      {
        const bool changed = value != value_;
        value = value_;
        if(changed)
          value_changed.emit(value);
      }

      bool operator==(const_reference other) { return other == value; }

      signal<value_type> value_changed;

      private:
        value_type value;
    };
  }
}
