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

#ifndef SKUI_CSS_OSTREAM_H
#define SKUI_CSS_OSTREAM_H

#include "css/color_stop.h++"
#include "css/time.h++"
#include "css/timing_function.h++"

#include "css/property/background.h++"

#include <iosfwd>

namespace skui::css
{
  class color;

  struct animation;
  struct background_size_width_height;
  struct background_size_auto;
  struct box_shadow;
  struct cubic_bezier;
  struct infinite_t;
  struct initial_t;
  struct inherit_t;
  struct length;
  struct length_with_offset;
  struct steps;
  struct position;

  enum class animation_direction : std::uint8_t;
  enum class fill_mode : std::uint8_t;
  enum class play_state : std::uint8_t;
  enum class unit : std::uint8_t;
  enum class background_size_keyword : std::uint8_t;
  enum class box_decoration_break : std::uint8_t;

  template<typename... ValueTypes>
  std::ostream& operator<<(std::ostream& os, const std::variant<ValueTypes...>& value)
  {
    std::visit([&os](auto&& v) { os << v; }, value);
    return os;
  }
  template<typename ValueType>
  std::ostream& operator<<(std::ostream& os, const std::optional<ValueType>& value)
  {
    if(value)
      return os << *value;
    else
      return os << "none";
  }

  std::ostream& operator<<(std::ostream& os, const inherit_t& inherit);
  std::ostream& operator<<(std::ostream& os, const initial_t& initial);

  std::ostream& operator<<(std::ostream& os, const color& color);
  template<typename ColorStopType>
  std::ostream& operator<<(std::ostream& os, const color_stop<ColorStopType>& color_stop);
  template<typename ColorStopType>
  std::ostream& operator<<(std::ostream& os,
                           const std::vector<skui::css::color_stop<ColorStopType>>& colors);

  std::ostream& operator<<(std::ostream& os, const unit unit);
  std::ostream& operator<<(std::ostream& os, const length& length);

  std::ostream& operator<<(std::ostream& os, const length_with_offset& length_with_offset);
  std::ostream& operator<<(std::ostream& os, const position& position);

  std::ostream& operator<<(std::ostream& os, const css::time& time);

  std::ostream& operator<<(std::ostream& os, const steps& steps);
  std::ostream& operator<<(std::ostream& os, const cubic_bezier& cubic_bezier);
  std::ostream& operator<<(std::ostream& os, const timing_function& timing_function);

  std::ostream& operator<<(std::ostream& os, const animation_direction&);
  std::ostream& operator<<(std::ostream& os, const fill_mode&);
  std::ostream& operator<<(std::ostream& os, const play_state&);
  std::ostream& operator<<(std::ostream& os, const timing_function&);
  std::ostream& operator<<(std::ostream& os, const infinite_t&);
  std::ostream& operator<<(std::ostream& os, const animation& animation);

  std::ostream& operator<<(std::ostream& os, const linear_gradient& linear_gradient);

  std::ostream& operator<<(std::ostream& os, radial_gradient::extent extent);
  std::ostream& operator<<(std::ostream& os, graphics::size2D<length>& size);
  std::ostream& operator<<(std::ostream& os, const radial_gradient::circle& circle);
  std::ostream& operator<<(std::ostream& os, const radial_gradient::ellipse& ellipse);
  std::ostream& operator<<(std::ostream& os, const std::variant<radial_gradient::circle, radial_gradient::ellipse>& shape_size);
  std::ostream& operator<<(std::ostream& os, const radial_gradient& radial_gradient);

  std::ostream& operator<<(std::ostream& os, const conic_gradient& conic_gradient);

  std::ostream& operator<<(std::ostream& os, const background_size_auto_t&);
  std::ostream& operator<<(std::ostream& os, const background_size_keyword& background_size_keyword);
  std::ostream& operator<<(std::ostream& os, const background_size_width_height& width_height);
  std::ostream& operator<<(std::ostream& os, const std::variant<core::string, linear_gradient, radial_gradient>& background_image);

  std::ostream& operator<<(std::ostream& os, box_decoration_break box_decoration_break);
  std::ostream& operator<<(std::ostream& os, const box_shadow& box_shadow);
}

template<typename ColorStopType>
std::ostream& skui::css::operator<<(std::ostream& os, const color_stop<ColorStopType>& color_stop)
{
  os << "color-stop(" << color_stop.color;
  if(color_stop.stop)
  {
    os << ", " << *color_stop.stop;
  }
  return os << ")";
}

template<typename ColorStopType>
std::ostream& skui::css::operator<<(std::ostream& os,
                                    const std::vector<skui::css::color_stop<ColorStopType>>& colors)
{
  for(auto it = colors.begin(); it != colors.end(); ++it)
  {
    os << *it;
    if(it+1 != colors.end())
      os << ", ";
  }
  return os;
}

#endif
