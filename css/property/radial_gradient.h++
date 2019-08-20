/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
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

#include <utility>
#include <variant>

#include <cinttypes>

namespace skui::css
{
  struct radial_gradient : background_gradient
  {
    enum class shape : std::uint8_t
    {
      ellipse,
      circle
    };

    enum class extent : std::uint8_t
    {
      farthest_corner,
      closest_side,
      closest_corner,
      farthest_side
    };

    struct shape_extent
    {
      radial_gradient::shape shape;
      radial_gradient::extent extent;
    };

    struct ellipse_size
    {
      length horizontal;
      length vertical;
    };

    // Either a shape+extent, or it's a circle with one radius, or an ellipse with two dimensions
    using shape_size_t = std::variant<shape_extent, length, ellipse_size>;
    shape_size_t shape_size;
    css::position position;
  };

  constexpr bool operator==(const radial_gradient::shape_extent& lhs,
                            const radial_gradient::shape_extent& rhs)
  {
    return lhs.shape == rhs.shape
        && lhs.extent == rhs.extent;
  }
  constexpr bool operator==(const radial_gradient::ellipse_size& lhs,
                            const radial_gradient::ellipse_size& rhs)
  {
    return lhs.horizontal == rhs.horizontal
        && lhs.vertical == rhs.vertical;
  }
  constexpr bool operator==(const radial_gradient& lhs,
                            const radial_gradient& rhs)
  {
      return static_cast<const background_gradient&>(lhs) == static_cast<const background_gradient&>(rhs)
          //&& lhs.shape_size == rhs.shape_size
          && lhs.position == rhs.position;
  }
}

#endif
