/**
 * The MIT License (MIT)
 *
 * Copyright © 2019-2020 Ruben Van Boxem
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

#ifndef SKUI_CSS_RADIAL_GRADIENT_H
#define SKUI_CSS_RADIAL_GRADIENT_H

#include "css/property/background_gradient.h++"

#include "css/length.h++"
#include "css/position.h++"

#include "graphics/size.h++"

#include <utility>
#include <variant>

#include <cinttypes>

namespace skui::css
{
  struct radial_gradient : background_gradient<length>
  {
    enum class extent : std::uint8_t
    {
      farthest_corner,
      closest_side,
      closest_corner,
      farthest_side
    };

    struct circle
    {
      std::variant<extent, length> radius;
    };

    struct ellipse
    {
      std::variant<extent, graphics::size2D<length>> size;
    };

    std::variant<ellipse, circle> shape;
    css::position position;
  };

  constexpr bool operator==(const radial_gradient::circle& lhs,
                            const radial_gradient::circle& rhs)
  {
    return lhs.radius == rhs.radius;
  }

  constexpr bool operator==(const radial_gradient::ellipse& lhs,
                            const radial_gradient::ellipse& rhs)
  {
    return lhs.size == rhs.size;
  }

  constexpr bool operator==(const radial_gradient& lhs,
                            const radial_gradient& rhs)
  {
    return static_cast<const background_gradient<length>&>(lhs) == static_cast<const background_gradient<length>&>(rhs)
        && lhs.shape == rhs.shape
        && lhs.position == rhs.position;
  }
}

#endif
