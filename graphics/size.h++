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
 * Size
 * Width and height properties in one nice package.
 */

#ifndef SKUI_GRAPHICS_SIZE_H
#define SKUI_GRAPHICS_SIZE_H

#include "graphics/pixel.h++"
#include "graphics/scalar.h++"

#include <core/utility/bound.h++>
#include <core/utility/norm.h++>

#include <limits>
#include <cmath>
#include <iostream>

namespace skui
{
  namespace graphics
  {
    template<typename ValueType>
    struct size2D
    {
      using value_type = ValueType;

      value_type width;
      value_type height;

      constexpr size2D& operator+=(const size2D& other);
      constexpr size2D& operator-=(const size2D& other);
      template<typename FactorType>
      constexpr size2D& operator*=(const FactorType& factor);
      template<typename FactorType>
      constexpr size2D& operator/=(const FactorType& factor);
    };

    template<typename ValueType>
    constexpr bool operator==(const size2D<ValueType>& left, const size2D<ValueType>& right)
    {
      return left.width == right.width && left.height == right.height;
    }
    template<typename ValueType>
    constexpr bool operator!=(const size2D<ValueType>& left, const size2D<ValueType>& right)
    {
      return left.width != right.width || left.height != right.height;
    }
    template<typename ValueType>
    constexpr size2D<ValueType>& size2D<ValueType>::operator+=(const size2D<ValueType>& other)
    {
      width += other.width;
      height += other.height;

      return *this;
    }
    template<typename ValueType>
    constexpr size2D<ValueType>& size2D<ValueType>::operator-=(const size2D<ValueType>& other)
    {
      width -= other.width;
      height -= other.height;

      return *this;
    }
    template<typename ValueType>
    template<typename FactorType>
    constexpr size2D<ValueType>& size2D<ValueType>::operator*=(const FactorType& factor)
    {
      width *= factor;
      height *= factor;

      return *this;
    }
    template<typename ValueType>
    template<typename FactorType>
    constexpr size2D<ValueType>& size2D<ValueType>::operator/=(const FactorType& factor)
    {
      width /= factor;
      height /= factor;

      return *this;
    }
    template<typename ValueType>
    constexpr size2D<ValueType> operator+(const size2D<ValueType>& left, const size2D<ValueType>& right)
    {
      return {left.width + right.width, left.height + right.height};
    }
    template<typename ValueType>
    constexpr size2D<ValueType> operator-(const size2D<ValueType>& left, const size2D<ValueType>& right)
    {
      return {left.width - right.width, left.height - right.height};
    }
    template<typename ValueType, typename FactorType>
    constexpr size2D<ValueType> operator*(const size2D<ValueType>& size, FactorType factor)
    {
      return {size.width*static_cast<ValueType>(factor), size.height*static_cast<ValueType>(factor)};
    }
    template<typename ValueType, typename FactorType>
    constexpr size2D<ValueType> operator/(const size2D<ValueType>& size, FactorType factor)
    {
      return {size.width/static_cast<ValueType>(factor), size.height/static_cast<ValueType>(factor)};
    }

    template<typename ValueType>
    std::ostream& operator<<(std::ostream& os, const size2D<ValueType>& size)
    {
      return os << '[' << size.width << ", " << size.height << ']';
    }

    // pixel here means "device independent pixel" aka scaled from 72dpi
    using pixel_size = size2D<pixel>;
    using scalar_size = size2D<scalar>;
  }

  namespace core
  {
    template<typename ValueType>
    struct bound<graphics::size2D<ValueType>>
    {
      constexpr graphics::size2D<ValueType> operator()(const graphics::size2D<ValueType>& value,
                                                       const graphics::size2D<ValueType>& lower_bound,
                                                       const graphics::size2D<ValueType>& upper_bound) const
      {
        return {bound<ValueType>{}(value.width, lower_bound.width, upper_bound.width),
                bound<ValueType>{}(value.height, lower_bound.height, upper_bound.height)};
      }
    };
    template<typename ValueType>
    struct norm<graphics::size2D<ValueType>>
    {
      constexpr ValueType operator()(const graphics::size2D<ValueType>& value) const
      {
        return std::abs(value.width)+std::abs(value.height);
      }
    };
  }
}

namespace std
{
  template<typename ValueType>
  class numeric_limits<skui::graphics::size2D<ValueType>> : public numeric_limits<ValueType>
  {
  private:
    using size = skui::graphics::size2D<ValueType>;
    using base = numeric_limits<ValueType>;

  public:
    static constexpr size min()
    {
      return { base::min(), base::min() };
    }
    static constexpr size lowest()
    {
      return { base::lowest(), base::lowest() };
    }
    static constexpr size max()
    {
      return { base::max(), base::max() };
    }
  };
}

#endif
