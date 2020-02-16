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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

/*
 * Number of bits
 * Determines the number of bits in an integral or enumeration type.
 */

#ifndef SKUI_CORE_TRAITS_NUMBER_OF_BITS_H
#define SKUI_CORE_TRAITS_NUMBER_OF_BITS_H

#include <limits>
#include <type_traits>

namespace skui::core
{
  template<typename Type, bool IsEnum = std::is_enum_v<Type>>
  struct number_of_bits : std::integral_constant<std::size_t, sizeof(Type)*std::numeric_limits<unsigned char>::digits> {};

  template<typename Enum>
  struct number_of_bits<Enum, true> : number_of_bits<std::underlying_type_t<Enum>> {};

  template<typename Type>
  constexpr auto number_of_bits_v = number_of_bits<Type>::value;
}

#endif
