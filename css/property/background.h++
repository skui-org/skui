/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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

#ifndef SKUI_CSS_PROPERTY_BACKGROUND_H
#define SKUI_CSS_PROPERTY_BACKGROUND_H

#include "css/property.h++"
#include "css/property/linear_gradient.h++"
#include "css/property/radial_gradient.h++"

#include "css/property/linear_gradient.h++"
#include "css/property/radial_gradient.h++"

#include <graphics/color.h++>
#include <graphics/size.h++>

#include <variant>

namespace skui::css
{
  enum class background_size_enum : std::uint8_t
  {
    cover,
    contain,
  };
  struct background_size_auto{};
  constexpr bool operator==(const background_size_auto&, const background_size_auto&) { return true; }

  enum class background_repeat : std::uint8_t
  {
    repeat,
    repeat_x,
    repeat_y,
    no_repeat,
    space,
    round,
  };

  using background_image = std::vector<std::variant<core::string,
                                                    linear_gradient,
                                                    radial_gradient>>;

  using background_size_length = std::variant<background_size_auto, length>;

  struct background_size_width_height
  {
    background_size_length width;
    background_size_length height;
  };

  constexpr bool operator==(const background_size_width_height& lhs,
                            const background_size_width_height& rhs)
  {
    return lhs.width == rhs.width
        && lhs.height == lhs.height;
  }

  using background_size = std::vector<std::variant<background_size_enum,
                                                   background_size_width_height>>;

  enum class background_origin : std::uint8_t
  {
    padding_box,
    border_box,
    content_box,
  };

  enum class background_clip : std::uint8_t
  {
    border_box,
    padding_box,
    content_box,
    text
  };

  enum class background_attachment : std::uint8_t
  {
    scroll,
    fixed,
    local,
  };

  struct background
  {
    property<css::color> color;
    property<background_image> image;
    property<std::vector<css::position>> position;
    property<background_size> size;
    property<background_repeat> repeat;
    property<background_origin> origin;
    property<background_clip> clip;
    property<background_attachment> attachment;
  };
}

#endif
