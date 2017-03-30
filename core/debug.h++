/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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
 * Debug
 * Helper facilities for debugging Skui, primarily meant for Skui development.
 */

#ifndef SKUI_CORE_DEBUG_H
#define SKUI_CORE_DEBUG_H

#include <iostream>

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#include <sstream>
#endif

namespace skui
{
  namespace core
  {
    template<typename... ArgTypes>

#ifndef SKUI_DEBUG
    inline void debug_print(ArgTypes...)
    {}
#else
    inline void debug_print(ArgTypes... args)
    {
      // trick to expand variadic argument pack without recursion
      using expand_variadic_pack  = int[];
      // first zero is to prevent empty braced-init-list
      // void() is to prevent overloaded operator, messing things up
      // trick is to use the side effect of list-initializer to call a function on every argument, in order.
      // (void) is to suppress "statement has no effect" warnings
#ifdef _WIN32
      std::stringstream stream;
      (void)expand_variadic_pack{0, ((stream << args), void(), 0)... };

      OutputDebugStringW(convert_to_utf16(stream.str()).c_str());
      //WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), stuff.c_str(), static_cast<DWORD>(stuff.size()), nullptr, nullptr);
#else
      (void)expand_variadic_pack{0, ((std::cerr << args), void(), 0)... };
#endif
    }
 #endif
  }
}

#endif
