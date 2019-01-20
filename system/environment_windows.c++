/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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

#include "system/environment.h++"

#include "core/debug.h++"
#include "core/utility.h++"

#include <windows.h>

namespace skui::system
{
  core::string get_environment_variable(const core::string& name)
  {
    const std::wstring wchar_name = core::convert_to_utf16(name);
    SetLastError(ERROR_SUCCESS);
    DWORD size = GetEnvironmentVariableW(wchar_name.c_str(), nullptr, 0);
    if(GetLastError() == ERROR_ENVVAR_NOT_FOUND)
      return {};

    std::wstring buffer;
    buffer.resize(size);
    if(GetEnvironmentVariableW(wchar_name.c_str(), &buffer[0], size) == size-1) // on success, this does not include the terminating '\0'
    {
      buffer.resize(size-1); // cut off the terminating null as std::string handles it by itself
      skui::core::debug_print(core::convert_to_utf8(buffer), '\n');
      return core::convert_to_utf8(buffer);
    }
    return {};
  }

  void set_environment_variable(const core::string& name, const core::string& value)
  {
    std::wstring wchar_name = core::convert_to_utf16(name);
    std::wstring wchar_value = core::convert_to_utf16(value);

    SetEnvironmentVariableW(wchar_name.c_str(), wchar_value.c_str());
  }

  void erase_environment_variable(const core::string& name)
  {
    const std::wstring wchar_name = core::convert_to_utf16(name);

    SetEnvironmentVariableW(wchar_name.c_str(), nullptr);
  }
}

