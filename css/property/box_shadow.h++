/**
 * The MIT License (MIT)
 *
 * Copyright © 2020 Ruben Van Boxem
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

#ifndef SKUI_CSS_PROPERTY_BOX_SHADOW_H
#define SKUI_CSS_PROPERTY_BOX_SHADOW_H

#include "css/color.h++"
#include "css/length.h++"

#include <optional>
#include <vector>

namespace skui::css
{
  struct box_shadow
  {
    bool inset{};
    length x_offset;
    length y_offset;
    length blur_radius;
    length spread_radius;
    std::optional<css::color> color;
  };

  constexpr bool operator==(const box_shadow& lhs, const box_shadow& rhs)
  {
    return lhs.inset == rhs.inset
        && lhs.x_offset == rhs.x_offset
        && lhs.y_offset == rhs.y_offset
        && lhs.blur_radius == rhs.blur_radius
        && lhs.spread_radius == rhs.spread_radius
        && lhs.color == rhs.color;
  }

  using box_shadows = std::vector<box_shadow>;
}

#endif
