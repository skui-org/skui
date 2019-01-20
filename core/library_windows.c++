/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

#include "core/library.h++"

#include "core/path.h++"
#include "core/utility.h++"

#ifndef WINDOWS_LEAN_AND_MEAN
#define WINDOWS_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <array>

namespace skui::core
{
  namespace implementation
  {
    constexpr char dll_prefix[] = "lib";
    constexpr char dll_suffix[] = ".dll";

    fs::path executable_path()
    {
      std::wstring buffer;
      buffer.resize(MAX_PATH);
      DWORD size = GetModuleFileNameW(nullptr, &buffer[0], MAX_PATH);
      buffer.resize(size);
      buffer.shrink_to_fit();
      return fs::path(buffer).remove_filename();
    }

    void* load(const path& filename)
    {
      const path filename_only = filename.filename();
      const path directory =  filename_only == filename.filename() ? executable_path()
                                                                   : (fs::current_path() / filename).remove_filename();

      std::array<path, 3> filenames{{directory / filename_only,
                                     directory / filename_only + dll_suffix,
                                     directory / dll_prefix + filename_only + dll_suffix}};

      for(const auto& filepath : filenames)
      {
        // this should use path::native(), but this is equivalent here and also works on MinGW-w64 Clang
        void* handle = LoadLibraryW(filepath.wstring().c_str());
        if(handle)
          return handle;
      }
      return nullptr;
    }

    bool unload(void* handle)
    {
      return FreeLibrary(static_cast<HMODULE>(handle)) == 0;
    }
  }

  library::function_ptr library::resolve_symbol(const string& symbol_name)
  {
    FARPROC function_address = GetProcAddress(static_cast<HMODULE>(native_handle), symbol_name.c_str());
    return function_ptr(function_address);
  }
}
