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

#ifndef SKUI_CSS_PROPERTY_ANIMATION_H
#define SKUI_CSS_PROPERTY_ANIMATION_H

#include "css/property.h++"
#include "css/time.h++"
#include "css/timing_function.h++"

#include <core/string.h++>

#include <iosfwd>

namespace skui::css
{
  enum class animation_direction : std::uint8_t
  {
    normal,
    reverse,
    alternate,
    alternate_reverse
  };
  enum class fill_mode : std::uint8_t
  {
    none,
    forwards,
    backwards,
    both
  };
  enum class play_state : std::uint8_t
  {
    running,
    paused
  };

  struct infinite_t final {} constexpr infinite;
  constexpr bool operator==(const infinite_t&, const infinite_t&) { return true; }

  using iteration_count = std::variant<std::uint64_t, infinite_t>;


  struct animation final
  {
    animation() = default;
    animation(const animation&) = default;
    animation(animation&&) = default;
    explicit animation(initial_t);
    explicit animation(inherit_t);
    animation& operator=(initial_t);
    animation& operator=(inherit_t);
    animation& operator=(const animation&) = default;
    animation& operator=(animation&&) = default;

    property<core::string> name;
    property<time> duration;
    property<css::timing_function> timing_function;
    property<time> delay;
    property<css::iteration_count> iteration_count;
    property<animation_direction> direction;
    property<css::fill_mode> fill_mode;
    property<css::play_state> play_state;
  };

  inline animation::animation(initial_t)
    : name{initial}
    , duration{initial}
    , timing_function{initial}
    , delay{initial}
    , iteration_count{initial}
    , direction{initial}
    , fill_mode{initial}
    , play_state(initial)
  {}

  inline animation::animation(inherit_t)
    : name{inherit}
    , duration{inherit}
    , timing_function{inherit}
    , delay{inherit}
    , iteration_count{inherit}
    , direction{inherit}
    , fill_mode{inherit}
    , play_state{inherit}
  {}

  inline animation& animation::operator=(initial_t)
  {
    *this = animation{initial};
    return *this;
  }

  inline animation& animation::operator=(inherit_t)
  {
    *this = animation{inherit};
    return *this;
  }

  constexpr bool operator==(const animation& left, const animation& right)
  {
    return left.name == right.name
        && left.duration == right.duration
        && left.timing_function == right.timing_function
        && left.delay == right.delay
        && left.iteration_count == right.iteration_count
        && left.direction == right.direction
        && left.fill_mode == right.fill_mode
        && left.play_state == right.play_state;
  }

  std::ostream& operator<<(std::ostream& os, const animation_direction&);
  std::ostream& operator<<(std::ostream& os, const fill_mode&);
  std::ostream& operator<<(std::ostream& os, const play_state&);
  std::ostream& operator<<(std::ostream& os, const timing_function&);
  std::ostream& operator<<(std::ostream& os, const infinite_t&);
  std::ostream& operator<<(std::ostream& os, const animation& animation);
}
#endif
