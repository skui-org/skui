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

#include <css/ostream.h++>

#include "css/test_rule.h++"

#include <css/grammar/background.h++>

namespace
{
  const auto background_image_url = "url(\"some/path\")";
  const auto background_image_urls = "url(\"some/path\"), url(\"other/path\")";
  const auto background_image_gradient_url = "linear-gradient(to top, red, blue), url(\"some/path\")";
  const auto background_image_none_url = "none, url(\"some/path\")";

  const auto background_size_cover_and_auto = "cover, auto";
  const auto background_size_width = "5 %";
  const auto background_size_auto_height = "auto 10px";
  const auto background_size_auto_contain = "auto, contain";
}

int main()
{
  using skui::test::check_rule_success;
  using skui::test::check_rule_failure;

  using skui::css::grammar::background_image;
  check_rule_success(background_image, background_image_url,
                     {"some/path"});
  check_rule_success(background_image, background_image_urls,
                     {"some/path", "other/path"});
  check_rule_success(background_image, background_image_gradient_url,
                     {skui::css::linear_gradient{{false,
                                                  {{skui::css::colors::red, {}},
                                                   {skui::css::colors::blue, {}}}},
                                                 skui::css::top},
                      "some/path"});
  check_rule_success(background_image, background_image_none_url,
                     {skui::core::string{},
                      "some/path"});

  using skui::css::grammar::background_size_width_height;
  check_rule_success(background_size_width_height, background_size_width,
                     skui::css::background_size_width_height{skui::css::length{5, skui::css::unit::percentage},
                                                             skui::css::background_size_auto});

  using skui::css::grammar::background_size;
  check_rule_success(background_size, background_size_cover_and_auto,
                     {skui::css::background_size_keyword::cover,
                      skui::css::background_size_width_height{skui::css::background_size_auto,
                                                              skui::css::background_size_auto}});

  check_rule_success(background_size, background_size_width,
                     {skui::css::background_size_width_height{skui::css::length{5, skui::css::unit::percentage},
                                                              skui::css::background_size_auto}});

  check_rule_success(background_size, background_size_auto_height,
                     {skui::css::background_size_width_height{skui::css::background_size_auto,
                                                              skui::css::length{10.f, skui::css::unit::px}}});
  check_rule_success(background_size, background_size_auto_contain,
                     {skui::css::background_size_width_height{skui::css::background_size_auto,
                                                              skui::css::background_size_auto},
                      skui::css::background_size_keyword::contain});

  return skui::test::exit_code;
}
