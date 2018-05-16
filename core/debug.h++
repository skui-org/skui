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
 * Debug
 * Helper facilities for debugging Skui, primarily meant for Skui development.
 */

#ifndef SKUI_CORE_DEBUG_H
#define SKUI_CORE_DEBUG_H

#include <iostream>

#ifdef _WIN32
#include "core/utility.h++"
#include <sstream>
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
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
#ifdef _WIN32
      std::stringstream stream;
      ((stream << args), ...);

      OutputDebugStringW(convert_to_utf16(stream.str()).c_str());
#else
      ((std::cerr << args), ...);
#endif
    }
#endif
  }
}

#endif
