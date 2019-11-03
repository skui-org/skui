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

#include "test.h++"

#include <core/string.h++>
#include <css/color.h++>

namespace
{
  using skui::test::check;
  using skui::core::string;

  void test_from_rgb()
  {
    {
      skui::css::color c{0xccaaffee};

      check(c.red == 0xcc, "red set correctly from uint32_t for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.green == 0xaa, "green set correctly from uint32_t for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.blue == 0xff, "blue set correctly from uint32_t for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.alpha == 0xee, "alpha set correctly from uint32_t for " + std::to_string(static_cast<std::uint32_t>(c)));
    }
    {
      auto c = skui::css::color::rgba(0xcc, 0xaa, 0xff, 0xee);

      check(c.red == 0xcc, "red set correctly for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.green == 0xaa, "green set correctly for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.blue == 0xff, "blue set correctly for " + std::to_string(static_cast<std::uint32_t>(c)));
      check(c.alpha == 0xee, "alpha set correctly for " + std::to_string(static_cast<std::uint32_t>(c)));
    }
  }

  void test_from_hsl()
  {
    check(skui::css::color::hsl(0, 0, 0) == skui::css::colors::black, "hsl(0,0,0) gives black");
    check(skui::css::color::hsl(0, 0, 1) == skui::css::colors::white, "hsl(0,0,1) gives white");
    check(skui::css::color::hsl(0, 1, 0) == skui::css::colors::black, "hsl(0,1,0) gives black");
    check(skui::css::color::hsl(0, 1, 1) == skui::css::colors::white, "hsl(0,1,1) gives white");
    check(skui::css::color::hsl(1, 0, 0) == skui::css::colors::black, "hsl(1,0,0) gives black");
    check(skui::css::color::hsl(1, 0, 1) == skui::css::colors::white, "hsl(1,0,1) gives white");
    check(skui::css::color::hsl(1, 1, 0) == skui::css::colors::black, "hsl(1,1,0) gives black");
    check(skui::css::color::hsl(1, 1, 1) == skui::css::colors::white, "hsl(1,1,1) gives white");

    check(skui::css::color::hsl(0, 0, .5) == skui::css::colors::gray, "hsl(0,0,.5) gives gray");
    check(skui::css::color::hsl(.5, 1, .5) == skui::css::colors::aqua, "hsl(180, 1, .5) gives aqua");
  }
}

int main()
{
  test_from_rgb();
  test_from_hsl();

  return skui::test::exit_code;
}
