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

/*
 * Bitflag
 * Convenience class template for bit flags.
 */

#ifndef SKUI_CORE_BITFLAG_H
#define SKUI_CORE_BITFLAG_H

#include "core/traits/number_of_bits.h++"

#include <bitset>
namespace skui
{
  namespace core
  {
    template<typename Enum>
    struct enum_is_bitflag : std::false_type {};

    template<typename Enum, std::size_t number_of_bits = number_of_bits_v<Enum>>
    class bitflag
    {
    public:
      constexpr bitflag() = default;
      bitflag(Enum value) : bits{enum_to_bits(value)} {}

      bitflag operator|(Enum value) const { bitflag result = *this; result.bits |= enum_to_bits(value); return result; }
      bitflag operator&(Enum value) const { bitflag result = *this; result.bits &= enum_to_bits(value); return result; }
      bitflag operator^(Enum value) const { bitflag result = *this; result.bits ^= enum_to_bits(value); return result; }
      bitflag operator~() const { bitflag result = *this; result.bits.flip(); return result; }

      bitflag& operator|=(Enum value) { bits |= enum_to_bits(value); return *this; }
      bitflag& operator&=(Enum value) { bits &= enum_to_bits(value); return *this; }
      bitflag& operator^=(Enum value) { bits ^= enum_to_bits(value); return *this; }

      bool any() const { return bits.any(); }
      bool all() const { return bits.all(); }
      bool none() const { return bits.none(); }
      std::size_t count() const { return bits.count(); }
      operator bool() { return any(); }

      bool test(Enum value) const { return *this & value; }
      void set(Enum value) { bits |= enum_to_bits(value); }
      void unset(Enum value) { bits &= ~enum_to_bits(value); }
      void clear() { bits.reset(); }

    private:
      std::bitset<number_of_bits> bits;

      template<typename SFINAE = Enum>
      static std::bitset<number_of_bits> enum_to_bits(std::enable_if_t<!enum_is_bitflag<SFINAE>::value, SFINAE> value)
      { return { 1ULL << static_cast<std::size_t>(value) }; }

      template<typename SFINAE = Enum>
      static std::bitset<number_of_bits> enum_to_bits(std::enable_if_t<enum_is_bitflag<SFINAE>::value, SFINAE> value)
      { return { static_cast<std::size_t>(value) }; }
    };

    namespace bitflag_operators
    {
      template<typename Enum>
      constexpr std::enable_if_t<std::is_enum<Enum>::value, bitflag<Enum>> operator|(Enum left, Enum right)
      {
        return bitflag<Enum>(left) | right;
      }
      template<typename Enum>
      constexpr std::enable_if_t<std::is_enum<Enum>::value, bitflag<Enum>> operator&(Enum left, Enum right)
      {
        return bitflag<Enum>(left) & right;
      }
      template<typename Enum>
      constexpr std::enable_if_t<std::is_enum<Enum>::value, bitflag<Enum>> operator^(Enum left, Enum right)
      {
        return bitflag<Enum>(left) ^ right;
      }
    }
  }
}

#endif
