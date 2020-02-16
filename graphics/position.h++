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
 * Size
 * Width and height properties in one nice package
 */

#ifndef SKUI_GRAPHICS_POSITION_H
#define SKUI_GRAPHICS_POSITION_H

#include "graphics/scalar.h++"

#include <core/utility/bound.h++>

#include <limits>
#include <tuple>

#include <cstdint>
#include <ostream>

namespace skui::graphics
{
  template<typename ValueType>
  struct position2D
  {
    using value_type = ValueType;

    value_type x;
    value_type y;

    constexpr position2D& operator+=(const position2D& other);
    constexpr position2D& operator-=(const position2D& other);
  };

  template<typename ValueType>
  std::ostream& operator<<(std::ostream& os, const position2D<ValueType>& position)
  {
    return os << '(' << position.x << ", " << position.y << ')';
  }

  template<typename ValueType>
  constexpr position2D<ValueType>& position2D<ValueType>::operator+=(const position2D<ValueType>& other)
  {
    x += other.x;
    y += other.y;

    return *this;
  }

  template<typename ValueType>
  constexpr position2D<ValueType>& position2D<ValueType>::operator-=(const position2D<ValueType>& other)
  {
    x -= other.x;
    y -= other.y;

    return *this;
  }

  template<typename ValueType>
  constexpr position2D<ValueType> operator+(const position2D<ValueType>& lhs,
                                            const position2D<ValueType>& rhs)
  {
    auto result = lhs;
    result += rhs;
    return result;
  }

  template<typename ValueType>
  constexpr position2D<ValueType> operator-(const position2D<ValueType>& lhs,
                                            const position2D<ValueType>& rhs)
  {
    auto result = lhs;
    result -= rhs;
    return result;
  }

  template<typename ValueType>
  constexpr bool operator==(const position2D<ValueType>& lhs,
                            const position2D<ValueType>& rhs)
  {
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
  }

  template<typename ValueType>
  constexpr bool operator!=(const position2D<ValueType>& lhs,
                            const position2D<ValueType>& rhs)
  {
    return !(lhs == rhs);
  }

  // pixel here means device independent pixel
  using pixel_position = position2D<std::int32_t>;
  using scalar_position = position2D<scalar>;
}

namespace skui::core
{
  template<typename ValueType>
  struct bound<graphics::position2D<ValueType>>
  {
  private:
    using position = graphics::position2D<ValueType>;
    using value_type = typename position::value_type;

  public:
    constexpr position operator()(const position& value,
                                  const position& min,
                                  const position& max) const
    {
      return {bound<value_type>{}(value.x, min.x, max.x),
            bound<value_type>{}(value.y, min.y, max.y)};
    }
  };
}

namespace std
{
  template<typename ValueType>
  struct numeric_limits<skui::graphics::position2D<ValueType>> : std::numeric_limits<ValueType>
  {
  private:
    using position = skui::graphics::position2D<ValueType>;
    using base = std::numeric_limits<ValueType>;

  public:
    static constexpr position min()
    {
      return { base::min(), base::min() };
    }
    static constexpr position lowest()
    {
      return { base::lowest(), base::lowest() };
    }
    static constexpr position max()
    {
      return { base::max(), base::max() };
    }
  };
}

#endif
