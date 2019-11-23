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

#include "css/test_rule.h++"

#include <css/grammar/position.h++>
#include <css/ostream.h++>

namespace
{
  using skui::core::string;

  const auto top_left = "top left";
  const auto top_center = "top center";
  const auto top_right = "top right";
  const auto center_left = "center left";
  const auto center_center = "center center";
  const auto center_right = "center right";
  const auto bottom_left = "bottom left";
  const auto bottom_center = "bottom center";
  const auto bottom_right = "bottom right";

  const auto left_top = "left top";
  const auto left_center = "left center";
  const auto left_bottom = "left bottom";
  const auto center_top = "center top";
  const auto center_bottom = "center bottom";
  const auto right_top = "right top";
  const auto right_center = "right center";
  const auto right_bottom = "right bottom";

  const auto top = "top";
  const auto center = "center";
  const auto bottom = "bottom";
  const auto left = "left";
  const auto right = "right";

  const auto relative_x = "2%";
  const auto relative_y = "left 4%";
  const auto relative_x_y = "6% 8%";
  const auto relative_x_offset = "left 20px";
  const auto relative_y_offset = "bottom -10px";
  const auto relative_x_y_offset = "left 5px center 10px";
  const auto relative_y_x_offset = "center 10px right 20px";

  const auto absolute_x = "20em";
  const auto absolute_x_y = "10in 20pt";

  const auto absolute_x_relative_y = "2 vw bottom 3pt";
  const auto absolute_y_relative_x = "bottom -2em right";

  const auto zero_x_relative_y = "0 bottom -3px";
  const auto absolute_x_zero_y = "2px 0";
  const auto zero_x_zero_y = "0 0";

}

int main()
{
  using skui::test::check_rule_success;

  using skui::css::grammar::position;
  using skui::css::unit;

  check_rule_success(position, top_left, skui::css::top_left);
  check_rule_success(position, top_center, skui::css::top_center);
  check_rule_success(position, top_right, skui::css::top_right);
  check_rule_success(position, center_left, skui::css::center_left);
  check_rule_success(position, center_center, skui::css::center_center);
  check_rule_success(position, center_right, skui::css::center_right);
  check_rule_success(position, bottom_left, skui::css::bottom_left);
  check_rule_success(position, bottom_center, skui::css::bottom_center);
  check_rule_success(position, bottom_right, skui::css::bottom_right);

  check_rule_success(position, left_top, skui::css::top_left);
  check_rule_success(position, left_center, skui::css::center_left);
  check_rule_success(position, left_bottom, skui::css::bottom_left);
  check_rule_success(position, center_top, skui::css::top_center);
  check_rule_success(position, center_bottom, skui::css::bottom_center);
  check_rule_success(position, right_top, skui::css::top_right);
  check_rule_success(position, right_center, skui::css::center_right);
  check_rule_success(position, right_bottom, skui::css::bottom_right);

  check_rule_success(position, top, skui::css::top);
  check_rule_success(position, center, skui::css::center);
  check_rule_success(position, bottom, skui::css::bottom);
  check_rule_success(position, left, skui::css::left);
  check_rule_success(position, right, skui::css::right);

  check_rule_success(position, relative_x, skui::css::position{{{2, unit::percentage}, {}},
                                                               {{50, unit::percentage}, {}}});
  check_rule_success(position, relative_y, skui::css::position{{{0, unit::percentage}, {4, unit::percentage}},
                                                               {{50, unit::percentage}, {}}});
  check_rule_success(position, relative_x_y, skui::css::position{{{6, unit::percentage}, {}},
                                                                 {{8, unit::percentage}, {}}});
  check_rule_success(position, relative_x_offset, skui::css::position{{{0, unit::percentage}, {20, unit::px}},
                                                                      {{50, unit::percentage}, {}}});
  check_rule_success(position, relative_y_offset, skui::css::position{{{50, unit::percentage}, {}},
                                                                      {{100, unit::percentage}, {-10, unit::px}}});
  check_rule_success(position, relative_x_y_offset, skui::css::position{{{0, unit::percentage}, {5, unit::px}},
                                                                        {{50, unit::percentage}, {10, unit::px}}});
  check_rule_success(position, relative_y_x_offset, skui::css::position{{{100, unit::percentage}, {20, unit::px}},
                                                                        {{50, unit::percentage}, {10, unit::px}}});

  check_rule_success(position, absolute_x, skui::css::position{{{20, unit::em}, {}},
                                                      {{50, unit::percentage}, {}}});
  check_rule_success(position, absolute_x_y, skui::css::position{{{10, unit::in}, {}},
                                                        {{20, unit::pt}, {}}});
  check_rule_success(position, absolute_x_relative_y, skui::css::position{{{2, unit::vw}, {}},
                                                                 {{100, unit::percentage}, {3, unit::pt}}});
  check_rule_success(position, absolute_y_relative_x, skui::css::position{{{100, unit::percentage}, {}},
                                                                 {{100, unit::percentage}, {-2, unit::em}}});

  check_rule_success(position, zero_x_relative_y, skui::css::position{{{0, unit::percentage}, {}},
                                                                      {{100, unit::percentage}, {-3, unit::px}}});
  check_rule_success(position, absolute_x_zero_y, skui::css::position{{{2, unit::px}, {}},
                                                             {{0, unit::percentage}, {}}});
  check_rule_success(position, zero_x_zero_y, skui::css::position{{{0, unit::percentage}, {}},
                                                                  {{0, unit::percentage}, {}}});
  return skui::test::exit_code;
}
