/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2018 Ruben Van Boxem
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

#include <core/traits/number_of_bits.h++>
#include <core/debug.h++>

namespace
{
  enum Enum {};
  enum class EnumClass {};
  enum class EnumClassChar : char {};
}
int main()
{
  using skui::core::number_of_bits_v;

  constexpr std::size_t bytes_in_a_char = std::numeric_limits<unsigned char>::digits;

  static_assert(number_of_bits_v<int> == sizeof(int)*bytes_in_a_char);
  static_assert(number_of_bits_v<Enum> == sizeof(Enum)*bytes_in_a_char);
  static_assert(number_of_bits_v<EnumClass> == sizeof(EnumClass)*bytes_in_a_char);
  static_assert(number_of_bits_v<EnumClassChar> == sizeof(EnumClassChar)*bytes_in_a_char);

  return skui::test::exit_code;
}
