/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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
 * css::declaration_block
 * In memory representation of CSS declaration block.
 */

#ifndef SKUI_CSS_DECLARATION_BLOCK_H
#define SKUI_CSS_DECLARATION_BLOCK_H

#include "css/property/animation_iteration_count.h++"
#include "css/property/background.h++"
#include "css/property/border.h++"

#include <core/string.h++>

#include <chrono>
#include <cstdint>

namespace skui::css
{
  using std::chrono::milliseconds;

  enum class align_content : std::uint8_t;
  enum class align_items : std::uint8_t;
  enum class align_self : std::uint8_t;
  enum class animation_direction : std::uint8_t;
  enum class animation_fill_mode : std::uint8_t;
  enum class animation_play_state : std::uint8_t;
  enum class backface_visibility : std::uint8_t;

  struct declaration_block
  {
    property<css::align_content> align_content{};
    property<css::align_items> align_items{};
    property<css::align_self> align_self{};
    property<milliseconds> animation_delay{};
    property<css::animation_direction> animation_direction{};
    property<milliseconds> animation_duration{};
    property<css::animation_fill_mode> animation_fill_mode{};
    property<css::animation_iteration_count> animation_iteration_count{css::animation_iteration_count{1}};
    property<core::string> animation_name{};
    property<css::animation_play_state> animation_play_state{};
    //css::animation_timing_function animation_timing_function{};
    css::property<css::backface_visibility> backface_visibility{};
    css::background background{};
    css::border border{};
    // border_bottom,
    // border_bottom_color,
    // border_bottom_left_radius,
    // border_bottom_right_radius,
    // border_bottom_style,
    // border_bottom_width,
    // border_collapse,
    // border_color,
    // border_image,
    // border_image_outset,
    // border_image_repeat,
    // border_image_slice,
    // border_image_source,
    // border_image_width,
    // border_left,
    // border_left_color,
    // border_left_style,
    // border_left_width,
    // border_radius,
    // border_right,
    // border_right_color,
    // border_right_style,
    // border_right_width,
    // border_spacing,
    // border_style,
    // border_top,
    // border_top_color,
    // border_top_left_radius,
    // border_top_right_radius,
    // border_top_style,
    // border_top_width,
    // border_width,
    // bottom,
    // box_decoration_break,
    // box_shadow,
    // box_sizing,
    // caption_side,
    // caret_color,
    // charset, // @charset
    // clear,
    // clip,
    // color,
    // column_count,
    // column_fill,
    // column_gap,
    // column_rule,
    // column_rule_color,
    // column_rule_style,
    // column_rule_width,
    // column_span,
    // column_width,
    // columns,
    // content,
    // counter_increment,
    // counter_reset,
    // cursor,
    // direction,
    // display,
    // empty_cells,
    // filter,
    // flex,
    // flex_basis,
    // flex_direction,
    // flex_flow,
    // flex_grow,
    // flex_shrink,
    // flex_wrap,
    // float_, // float
    // font,
    // font_face, // @font_face
    // font_family,
    // font_kerning,
    // font_size,
    // font_size_adjust,
    // font_stretch,
    // font_style,
    // font_variant,
    // font_weight,
    // grid,
    // grid_area,
    // grid_auto_columns,
    // grid_auto_flow,
    // grid_auto_rows,
    // grid_column,
    // grid_column_end,
    // grid_column_gap,
    // grid_column_start,
    // grid_gap,
    // grid_row,
    // grid_row_end,
    // grid_row_gap,
    // grid_row_start,
    // grid_template,
    // grid_template_areas,
    // grid_template_columns,
    // grid_template_rows,
    // hanging_punctuation,
    // height,
    // hyphens,
    // import, // @import
    // isolation,
    // justify_content,
    // keyframes, // @keyframes
    // left,
    // letter_spacing,
    // line_height,
    // list_style,
    // list_style_image,
    // list_style_position,
    // list_style_type,
    // margin,
    // margin_bottom,
    // margin_left,
    // margin_right,
    // margin_top,
    // max_height,
    // max_width,
    // media, // @media
    // min_height,
    // min_width,
    // mix_blend_mode,
    // object_fit,
    // object_position,
    // opacity,
    // order,
    // outline,
    // outline_color,
    // outline_offset,
    // outline_style,
    // outline_width,
    // overflow,
    // overflow_x,
    // overflow_y,
    // padding,
    // padding_bottom,
    // padding_left,
    // padding_right,
    // padding_top,
    // page_break_after,
    // page_break_before,
    // page_break_inside,
    // perspective,
    // perspective_origin,
    // pointer_events,
    // position,
    // quotes,
    // resize,
    // right,
    // scroll_behavior,
    // tab_size,
    // table_layout,
    // text_align,
    // text_align_last,
    // text_decoration,
    // text_decoration_color,
    // text_decoration_line,
    // text_decoration_style,
    // text_indent,
    // text_justify,
    // text_overflow,
    // text_shadow,
    // text_transform,
    // top,
    // transform,
    // transform_origin,
    // transform_style,
    // transition,
    // transition_delay,
    // transition_duration,
    // transition_property,
    // transition_timing_function,
    // unicode_bidi,
    // user_select,
    // vertical_align,
    // visibility,
    // white_space,
    // width,
    // word_break,
    // word_spacing,
    // word_wrap,
    // z_index
  };

  constexpr bool operator==(const declaration_block& left, const declaration_block& right)
  {
    return left.align_content == right.align_content
        && left.align_items == right.align_items
        && left.align_self == right.align_self;
  }
}

#endif
