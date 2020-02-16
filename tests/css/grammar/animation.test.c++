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

#include "css/test_rule.h++"

#include <css/grammar/animation.h++>
#include <css/ostream.h++>

namespace
{
  using namespace std::chrono_literals;
  using skui::core::string;

  using skui::css::animation;

  const string full_animation_ordered_input = "my_name 20s linear 5s 2 alternate both paused";
  animation full_animation_ordered()
  {
    animation a;
    a.name = "my_name";
    a.duration = 20s;
    a.timing_function = skui::css::linear;
    a.delay = 5s;
    a.iteration_count = 2ul;
    a.direction = skui::css::animation_direction::alternate;
    a.fill_mode = skui::css::fill_mode::both;
    a.play_state = skui::css::play_state::paused;

    return a;
  }
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  check_rule_success(skui::css::grammar::animation, full_animation_ordered_input,
                     full_animation_ordered());

  return skui::test::exit_code;
}
