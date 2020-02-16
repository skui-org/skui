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
 * Debug
 * Helper facilities for debugging Skui, primarily meant for Skui development.
 */

#ifndef SKUI_CORE_DEBUG_H
#define SKUI_CORE_DEBUG_H

#include "core/utility.h++"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include "core/utility.h++"
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#endif

namespace skui::core
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
#else
    auto& stream = std::cerr;
    core::ostream_format_keeper guard(stream);
#endif
    const auto now = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto time = std::chrono::system_clock::to_time_t(now);
    const auto utc_time = std::gmtime(&time);

    stream << std::put_time(utc_time, "%FT%T.")
           << std::setprecision(4) << std::setfill('0') << std::setw(3) << ms.count()
           << std::put_time(utc_time, "%z: ");
    stream << std::boolalpha;
    stream << std::setprecision(15);
    ((stream << args), ...);

#ifdef _WIN32
    OutputDebugStringW(convert_to_utf16(stream.str()).c_str());
#endif
  }
#endif
}

#endif
