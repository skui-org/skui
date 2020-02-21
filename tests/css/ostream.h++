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

#ifndef SKUI_TEST_CSS_OSTREAM_H
#define SKUI_TEST_CSS_OSTREAM_H

#include <css/color_stop.h++>
#include <css/time.h++>
#include <css/timing_function.h++>

#include <css/position.h++>

#include <css/property/align_content.h++>
#include <css/property/align_items.h++>
#include <css/property/align_self.h++>
#include <css/property/animation.h++>
#include <css/property/background.h++>
#include <css/property/box_decoration_break.h++>
#include <css/property/box_shadow.h++>
#include <css/property/box_sizing.h++>
#include <css/property/caption_side.h++>
#include <css/property/clear.h++>

#include <core/utility.h++>

#include <iomanip>
#include <iostream>

namespace skui::css
{
  template<typename... Types>
  std::ostream& operator<<(std::ostream& os, const std::vector<Types...>& values)
  {
    for(std::size_t i = 0; i<values.size(); ++i)
    {
      os << values[i] << ", ";
    }
    return os << values.back();
  }
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
  inline std::ostream& operator<<(std::ostream& os, const auto_t&)
  {
    return os << "auto";
  }

  inline std::ostream& operator<<(std::ostream& os, const inherit_t&)
  {
    return os << "inherit";
  }

  inline std::ostream& operator<<(std::ostream& os, const initial_t&)
  {
    return os << "initial";
  }

  inline std::ostream& operator<<(std::ostream& os, align_content align_content)
  {
    switch(align_content)
    {
      case css::align_content::stretch:
        return os << "stretch";
      case css::align_content::center:
        return os << "center";
      case css::align_content::flex_start:
        return os << "flex-start";
      case css::align_content::flex_end:
        return os << "flex-end";
      case css::align_content::space_between:
        return os << "space-between";
      case css::align_content::space_around:
        return os << "space-around";
    }
    return os;
  }
  inline std::ostream& operator<<(std::ostream& os, align_items align_items)
  {
    switch(align_items)
    {
      case css::align_items::stretch:
        return os << "stretch";
      case css::align_items::center:
        return os << "center";
      case css::align_items::flex_start:
        return os << "flex-start";
      case css::align_items::flex_end:
        return os << "flex-end";
      case css::align_items::baseline:
        return os << "baseline";
    }
    return os;
  }
  inline std::ostream& operator<<(std::ostream& os, align_self align_self)
  {
    switch(align_self)
    {
      case css::align_self::stretch:
        return os << "stretch";
      case css::align_self::center:
        return os << "center";
      case css::align_self::flex_start:
        return os << "flex-start";
      case css::align_self::flex_end:
        return os << "flex-end";
      case css::align_self::baseline:
        return os << "baseline";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, const color& color)
  {
    core::ostream_format_keeper keeper(os);

    return os << std::setfill('0') << std::setw(8) << std::hex << std::uint32_t(color);
  }

  inline std::ostream& operator<<(std::ostream& os, const unit unit)
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

  inline std::ostream& operator<<(std::ostream& os, const length& length)
  {
    return os << length.value << ' ' << length.unit;
  }

  inline std::ostream& operator<<(std::ostream& os, const length_with_offset& length_with_offset)
  {
    os << length_with_offset.value;
    if(length_with_offset.offset != length{})
    {
      os << " (offset: " << length_with_offset.offset << ')';
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, const position& position)
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

  template<typename ColorStopType>
  std::ostream& operator<<(std::ostream& os, const color_stop<ColorStopType>& color_stop)
  {
    os << "color-stop(" << color_stop.color;
    if(color_stop.stop)
    {
      os << ", " << *color_stop.stop;
    }
    return os << ")";
  }

  inline std::ostream& operator<<(std::ostream& os, const skui::css::time& time)
  {
    return os << time.count() << " ms";
  }

  inline std::ostream& operator<<(std::ostream& os, const steps& steps)
  {
    return os << "steps(" << steps.intervals << ", " << steps.change << ')';
  }

  inline std::ostream& operator<<(std::ostream& os, const cubic_bezier& cubic_bezier)
  {
    return os << "cubic-bezier(" << cubic_bezier.x1 << ", " << cubic_bezier.y1 << ", "
                                 << cubic_bezier.x2 << ", " << cubic_bezier.y2 << ')';
  }

  inline std::ostream& operator<<(std::ostream& os, const timing_function& timing_function)
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

  inline std::ostream& operator<<(std::ostream& os, const fill_mode& mode)
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

  inline std::ostream& operator<<(std::ostream& os, const play_state& state)
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

  inline std::ostream& operator<<(std::ostream& os, const infinite_t&)
  {
    return os << "infinite";
  }

  inline std::ostream& operator<<(std::ostream& os, const animation& animation)
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

  inline std::ostream& operator<<(std::ostream& os,
                                  const linear_gradient& linear_gradient)
  {
    if(linear_gradient.repeating)
      os << "repeating-";

    os << "linear-gradient(to ";
    std::visit([&os](auto&& direction) { os << direction; }, linear_gradient.direction);

    return os << ", " << linear_gradient.colors << ")";
  }

  inline std::ostream& operator<<(std::ostream& os,
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

  inline std::ostream& operator<<(std::ostream& os, const graphics::size2D<length>& size)
  {
    return os << '(' << size.width << ", " << size.height << ')';
  }

  inline std::ostream& operator<<(std::ostream& os, const radial_gradient::circle& circle)
  {
    return os << "circle " << circle.radius;
  }

  inline std::ostream& operator<<(std::ostream& os, const radial_gradient::ellipse& ellipse)
  {
    return os << "ellipse " << ellipse.size;
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

  inline std::ostream& operator<<(std::ostream& os, const background_size_keyword& background_size_keyword)
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

  inline std::ostream& operator<<(std::ostream& os, const background_size_width_height& width_height)
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

  inline std::ostream& operator<<(std::ostream& os, background_repeat background_repeat)
  {
    switch(background_repeat)
    {
      case background_repeat::repeat:
        return os << "repeat";
      case background_repeat::repeat_x:
        return os << "repeat-x";
      case background_repeat::repeat_y:
        return os << "repeat-y";
      case background_repeat::no_repeat:
        return os << "no-repeat";
      case background_repeat::space:
        return os << "space";
      case background_repeat::round:
        return os << "round";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, background_origin origin)
  {
    switch(origin)
    {
      case background_origin::padding_box:
        return os << "padding-box";
      case background_origin::border_box:
        return os << "border-box";
      case background_origin::content_box:
        return os << "content-box";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, const background_clip clip)
  {
    switch(clip)
    {
      case background_clip::border_box:
        return os << "border-box";
      case background_clip::padding_box:
        return os << "padding-box";
      case background_clip::content_box:
        return os << "content-box";
      case background_clip::text:
        return os << "text";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, background_attachment attachment)
  {
    switch(attachment)
    {
      case background_attachment::scroll:
        return os << "scroll";
      case background_attachment::fixed:
        return os << "fixed";
      case background_attachment::local:
        return os << "local";
    }
    return os;
  }
/*
  inline std::ostream& operator<<(std::ostream& os, const background_layer& background_layer)
  {
    return os << "background-color: " << background_layer.color << '\n'
              << "background-image: " << background_layer.image << '\n'
              << "background-position: " << background_layer.position << '\n'
              << "background-size: " << background_layer.size << '\n'
              << "background-repeat: " << background_layer.repeat << '\n'
              << "background-origin: " << background_layer.origin << '\n'
              << "background-clip: " << background_layer.clip << '\n'
              << "background-attachment; " << background_layer.attachment;
  }
*/
  inline std::ostream& operator<<(std::ostream& os, box_decoration_break box_decoration_break)
  {
    switch(box_decoration_break)
    {
      case css::box_decoration_break::slice:
        return os << "slice";
      case css::box_decoration_break::clone:
        return os << "clone";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, const box_shadow& box_shadow)
  {
    const core::ostream_format_keeper format_guard{os};

    return os << std::boolalpha
              << "inset: " << box_shadow.inset << '\n'
              << "x offset: " << box_shadow.x_offset << '\n'
              << "y offset: " << box_shadow.y_offset << '\n'
              << "blur radius: " << box_shadow.blur_radius << '\n'
              << "spread radius: " << box_shadow.spread_radius << '\n'
              << "color: " << box_shadow.color;
  }

  inline std::ostream& operator<<(std::ostream& os, box_sizing box_sizing)
  {
    switch(box_sizing)
    {
      case css::box_sizing::content_box:
        return os << "content-box";
      case css::box_sizing::border_box:
        return os << "border-box";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, caption_side caption_side)
  {
    switch(caption_side)
    {
      case css::caption_side::top:
        return os << "top";
      case css::caption_side::bottom:
        return os << "bottom";
    }
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, clear clear)
  {
    switch(clear)
    {
      case css::clear::none:
        return os << "none";
      case css::clear::left:
        return os << "left";
      case css::clear::right:
        return os << "right";
      case css::clear::both:
        return os << "both";
    }
    return os;
  }
}

#endif
