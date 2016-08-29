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

/*
 * Win32-specific implementation of application class/
 */

#include "application.h++"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

#include <codecvt>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

namespace skui
{
  namespace core
  {

    std::vector<string> application::initialize_arguments(int, char*[])
    {
      std::vector<string> result;

      int argc;
      wchar_t** argz = CommandLineToArgvW(GetCommandLineW(), &argc);
      result.reserve(static_cast<std::size_t>(argc));

      // convert to UTF-8
      try
      {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;

        for(int i = 1; i<argc; ++i)
        {
          result.emplace_back(converter.to_bytes(argz[i]));
        }
      }
      catch(const std::out_of_range&)
      {
        std::cerr << "Failure converting commandline arguments to UTF-8.\n";
        quit();
      }

      return result;
    }
  }
}
