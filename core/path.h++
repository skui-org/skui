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
 * Path
 * File/directory path class, currently just std:{:experimental:}::filesystem::path
 */

#ifndef SKUI_CORE_PATH_H
#define SKUI_CORE_PATH_H

#include <algorithm>
#include <iterator>

#if __has_include(<filesystem>)
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

namespace skui::core
{
#if __has_include(<filesystem>)
  namespace fs = std::filesystem;
#else
  namespace fs = std::experimental::filesystem;
#endif
  using path = fs::path;

  inline path operator+(const path& lhs, const path& rhs)
  {
    path::string_type result = lhs.native();
    result += rhs.native();
    return result;
  }
}

#endif
