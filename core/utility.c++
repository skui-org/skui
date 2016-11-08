/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ruben Van Boxem
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

#include "utility.h++"

#ifdef _WIN32
#include <stdexcept>
#ifndef WINDOWS_LEAN_AND_MEAN
#define WINDOWS_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace skui
{
  namespace core
  {
#ifdef _WIN32
    string convert_to_utf8(const std::wstring& utf16_string)
    {
      // get length
      int length = WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), static_cast<int>(utf16_string.size()),
                                       nullptr, 0, nullptr, nullptr);
      if(!(length > 0))
        return string();
      else
      {
        string result;
        result.resize(static_cast<string::size_type>(length));

        if(WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), static_cast<int>(utf16_string.size()),
                               &result[0], static_cast<int>(result.size()), nullptr, nullptr) == 0 )
          throw std::runtime_error("Failure to execute convert_to_utf8: call to WideCharToMultiByte failed.");
        else
          return result;
      }
    }
    std::wstring convert_to_utf16(const string& utf8_string)
    {
      // get length
      int length = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), static_cast<int>(utf8_string.size()), nullptr, 0);
      if(!(length > 0))
        return {};
      else
      {
        std::wstring result;
        result.resize(static_cast<string::size_type>(length));

        if(MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), static_cast<int>(utf8_string.size()),
                               &result[0], static_cast<int>(result.size())) == 0 )
          throw std::runtime_error("Failure to execute convert_to_utf16: call to MultiByteToWideChar failed.");
        else
          return result;
      }
    }
#endif
  }
}
