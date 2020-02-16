/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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
 * OUT OF OR IN CONnECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "test.h++"

#include <graphics/swizzle.h++>

namespace
{
  void test_swizzle()
  {
    std::uint32_t a = 0x00;
    std::uint32_t r = 0xAB;
    std::uint32_t g = 0xCD;
    std::uint32_t b = 0xEF;

    std::vector<std::uint32_t> argb { a << 24 | r << 16 | g << 8 | b << 0 };

    skui::graphics::swizzle(argb);

    std::uint32_t a_ = std::uint8_t(argb[0] >> 24);
    std::uint32_t b_ = std::uint8_t(argb[0] >> 16);
    std::uint32_t g_ = std::uint8_t(argb[0] >> 8);
    std::uint32_t r_ = std::uint8_t(argb[0] >> 0);

    skui::test::check(a_ == 0x00, "alpha unswizzled");
    skui::test::check(b_ == 0xEF, "r swizzled with b");
    skui::test::check(g_ == 0xCD, "g unswizzled");
    skui::test::check(r_ == 0xAB, "b swizzled with r");
  }
}

int main()
{
  test_swizzle();

  return skui::test::exit_code;
}
