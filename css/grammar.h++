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

/*
 * css::grammar
 * Rules are based on description at https://www.w3schools.com/css/css_syntax.asp
 */

#ifndef SKUI_CSS_GRAMMAR_H
#define SKUI_CSS_GRAMMAR_H

#include "css/declaration_block.h++"
#include "css/property.h++"
#include "css/rule_set.h++"

#include "css/grammar/align_content.h++"
#include "css/grammar/align_items.h++"
#include "css/grammar/align_self.h++"
#include "css/grammar/animation.h++"
#include "css/grammar/background.h++"
#include "css/grammar/backface_visibility.h++"
#include "css/grammar/color.h++"
#include "css/grammar/x3_stdvariant.h++"

#include "css/grammar/make_property.h++"

#include <boost/spirit/home/x3.hpp>

#include <unordered_map>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  const auto declaration = make_property("align-content", align_content, &css::declaration_block::align_content)
                         | make_property("align-items", align_items, &css::declaration_block::align_items)
                         | make_property("align-self", align_self, &css::declaration_block::align_self)
                      // | make_property("all", all, &css::declaration_block::all)
                         | make_property("animation", animation, &css::declaration_block::animation)
                         | make_property("animation-delay", animation_delay, &css::declaration_block::animation, &css::animation::delay)
                         | make_property("animation-direction", animation_direction, &css::declaration_block::animation, &css::animation::direction)
                         | make_property("animation-duration", animation_duration, &css::declaration_block::animation, &css::animation::duration)
                         | make_property("animation-fill-mode", animation_fill_mode, &css::declaration_block::animation, &css::animation::fill_mode)
                         | make_property("animation-iteration-count", animation_iteration_count, &css::declaration_block::animation, &css::animation::iteration_count)
                         | make_property("animation-name", animation_name, &css::declaration_block::animation, &css::animation::name)
                         | make_property("animation-play-state", animation_play_state, &css::declaration_block::animation, &css::animation::play_state)
                         | make_property("animation-timing-function", animation_timing_function, &css::declaration_block::animation, &css::animation::timing_function)
                         | make_property("backface-visibility", backface_visibility, &css::declaration_block::backface_visibility)
                         | make_property("background", background, &css::declaration_block::background)
                         | make_background_property("background-color", color, &css::background::color)
                         | make_background_property("background-image", background_image, &css::background::image)
                         | make_background_property("background-position", background_position, &css::background::position)
                         | make_background_property("background-size", background_size, &css::background::size)
                         | make_background_property("background-repeat", background_repeat, &css::background::repeat)
                         | make_background_property("background-origin", background_origin, &css::background::origin)
                         | make_background_property("background-clip", background_clip, &css::background::clip)
                         | make_background_property("background-attachment", background_attachment, &css::background::attachment)
                         ;

  const auto declaration_block = x3::rule<struct declaration_block, css::declaration_block>{"declaration_block"}
                               = '{' >> +declaration >> '}';
}

#endif
