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

#include "ostream.h++"

#include "css/position.h++"

#include "css/property/animation.h++"

#include <iomanip>
#include <iostream>

namespace skui::css
{
  std::ostream& operator<<(std::ostream& os, const inherit_t&)
  {
    return os << "inherit";
  }

  std::ostream& operator<<(std::ostream& os, const initial_t&)
  {
    return os << "initial";
  }

  std::ostream& operator<<(std::ostream& os, const color& color)
  {
    core::ostream_format_keeper keeper(os);

    return os << std::setfill('0') << std::setw(8) << std::hex << std::uint32_t(color);
  }

  std::ostream& operator<<(std::ostream& os, const unit unit)
  {
    switch(unit)
    {
      case unit::mm:
        return os << "mm";
      case unit::cm:
        return os << "cm";
      case unit::in:
        return os << "in";
      case unit::px:
        return os << "px";
      case unit::pt:
        return os << "pt";
      case unit::pc:
        return os << "pc";
      case unit::em:
        return os << "em";
      case unit::ex:
        return os << "ex";
      case unit::ch:
        return os << "ch";
      case unit::rem:
        return os << "rem";
      case unit::vw:
        return os << "vw";
      case unit::vh:
        return os << "vh";
      case unit::vmin:
        return os << "vmin";
      case unit::vmax:
        return os << "vmax";
      case unit::percentage:
        return os << "%";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const length& length)
  {
    return os << length.value << ' ' << length.unit;
  }

  std::ostream& operator<<(std::ostream& os, const length_with_offset& length_with_offset)
  {
    os << length_with_offset.value;
    if(length_with_offset.offset != length{})
    {
      os << " (offset: " << length_with_offset.offset << ')';
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const position& position)
  {
    if(position == top)
      os << "top";
    else if(position == center)
      os << "center";
    else if(position == bottom)
      os << "bottom";
    else if(position == left)
      os << "left";
    else if(position == right)
      os << "right";
    else if(position == top_left)
      os << "top left";
    else if(position == top_right)
      os << "top right";
    else if(position == bottom_left)
      os << "bottom left";
    else if(position == bottom_right)
      os << "bottom right";
    else
      os << "position(" << position.x << ", " << position.y << ")";

    return os;
  }

  std::ostream& operator<<(std::ostream& os, const skui::css::time& time)
  {
    return os << time.count() << " ms";
  }

  std::ostream& operator<<(std::ostream& os, const steps& steps)
  {
    return os << "steps(" << steps.intervals << ", " << steps.change << ')';
  }

  std::ostream& operator<<(std::ostream& os, const cubic_bezier& cubic_bezier)
  {
    return os << "cubic-bezier(" << cubic_bezier.x1 << ", " << cubic_bezier.y1 << ", "
                                 << cubic_bezier.x2 << ", " << cubic_bezier.y2 << ')';
  }

  std::ostream& operator<<(std::ostream& os, const timing_function& timing_function)
  {
    std::visit([&os](const auto& value) { os << value; }, timing_function);
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const animation_direction& direction)
  {
    switch(direction)
    {
      case animation_direction::normal:
        return os << "normal";
      case animation_direction::reverse:
        return os << "reverse";
      case animation_direction::alternate:
        return os << "alternate";
      case animation_direction::alternate_reverse:
        return os << "alternate-reverse";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const fill_mode& mode)
  {
    switch(mode)
    {
      case fill_mode::none:
        return os << "none";
      case fill_mode::forwards:
        return os << "forwards";
      case fill_mode::backwards:
        return os << "backwards";
      case fill_mode::both:
        return os << "both";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const play_state& state)
  {
    switch(state)
    {
      case play_state::running:
        return os << "running";
      case play_state::paused:
        return os << "paused";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const infinite_t&)
  {
    return os << "infinite";
  }

  std::ostream& operator<<(std::ostream& os, const animation& animation)
  {
    return os << "animation\n{\n"
                 "  name: " << animation.name << ";\n"
                 "  duration: " << /*animation.duration <<*/ ";\n"
                 "  timing-function: " << animation.timing_function << ";\n"
                 "  delay: " << /*animation.delay <<*/ ";\n"
                 "  iteration_count: " << animation.iteration_count << ";\n"
                 "  direction: " << animation.direction << ";\n"
                 "  fill_mode: " << animation.fill_mode << ";\n"
                 "  play_state: " << animation.play_state << ";\n"
                                                             "}";
  }

  std::ostream& operator<<(std::ostream& os,
                           const linear_gradient& linear_gradient)
  {
    if(linear_gradient.repeating)
      os << "repeating-";

    os << "linear-gradient(to ";
    std::visit([&os](auto&& direction) { os << direction; }, linear_gradient.direction);

    return os << ", " << linear_gradient.colors << ")";
  }

  std::ostream& operator<<(std::ostream& os,
                           radial_gradient::extent extent)
  {
    switch(extent)
    {
      case radial_gradient::extent::farthest_corner: return os << "farthest-corner";
      case radial_gradient::extent::closest_side: return os << "closest-side";
      case radial_gradient::extent::closest_corner: return os << "closest-corner";
      case radial_gradient::extent::farthest_side: return os << "farthest-side";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const graphics::size2D<length>& size)
  {
    return os << '(' << size.width << ", " << size.height << ')';
  }

  std::ostream& operator<<(std::ostream& os, const radial_gradient::circle& circle)
  {
    return os << "circle " << circle.radius;
  }

  std::ostream& operator<<(std::ostream& os, const radial_gradient::ellipse& ellipse)
  {
    return os << "ellipse " << ellipse.size;
  }

  std::ostream& operator<<(std::ostream& os, const std::variant<radial_gradient::circle, radial_gradient::ellipse>& shape_size)
  {
    std::visit([&os](auto&& v) { os << v; }, shape_size);

    return os;
  }

  std::ostream& operator<<(std::ostream& os,
                           const radial_gradient& radial_gradient)
  {
    if(radial_gradient.repeating)
      os << "repeating-";

    return os << "radial-gradient("
              << radial_gradient.shape << " at " << radial_gradient.position << ", "
              << radial_gradient.colors
              << ")";
  }

  std::ostream& operator<<(std::ostream& os, const std::variant<core::string, linear_gradient, radial_gradient>& background_image)
  {
    std::visit([&os](auto&& v) { os << v; }, background_image);

    return os;
  }

  std::ostream& operator<<(std::ostream& os, const background_size_keyword& background_size_keyword)
  {
    switch(background_size_keyword)
    {
      case css::background_size_keyword::cover:
        return os << "cover";
      case css::background_size_keyword::contain:
        return os << "contain";
    }
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const background_size_width_height& width_height)
  {
    return os << width_height.width << ' ' << width_height.height;
  }

  std::ostream& operator<<(std::ostream& os, const background_size_auto_t&)
  {
    return os << "auto";
  }

  std::ostream& operator<<(std::ostream& os, const conic_gradient& conic_gradient)
  {
    return os << "conic-gradient(from " << conic_gradient.from << ", "
                                "at " << conic_gradient.position << ", "
                              << conic_gradient.colors << ")";
  }

}
