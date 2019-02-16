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

#include "css/property/animation.h++"
#include "css/time.h++"

#include <iostream>
#include <variant>

namespace skui::css
{
  template<typename... ValueTypes>
  std::ostream& operator<<(std::ostream& os, const std::variant<ValueTypes...>& value)
  {
    std::visit([&os](auto&& v) { os << v; }, value);
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
}
