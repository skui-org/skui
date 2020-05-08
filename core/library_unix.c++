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

#include "core/library.h++"

#include "core/debug.h++"
#include "core/path.h++"

#include <dlfcn.h>

#include <array>

namespace skui::core
{
  namespace implementation
  {
    constexpr char so_suffix[] =
#ifdef __APPLE__
        ".dylib";
#else
        ".so";
#endif
    constexpr char so_prefix[] = "lib";

    void* load(const path& filename)
    {
      path directory = fs::absolute(filename).remove_filename();
      path filename_only = filename.filename();

      std::array<path, 3> filenames{{directory / filename_only,
                                     directory / (filename_only + so_suffix),
                                     directory / (so_prefix + filename_only + so_suffix)}};
      for(const auto& filename : filenames)
      {
        core::debug_print("skui::core::library: Attempting to load ", filename, '\n');
        void* handle = dlopen(filename.c_str(), RTLD_LAZY);
        if(handle)
          return handle;
      }
      return nullptr;
    }

    bool unload(void* handle)
    {
      return dlclose(handle);
    }
  }

  library::function_ptr library::resolve_symbol(const string& symbol_name)
  {
    return function_ptr(dlsym(native_handle, symbol_name.c_str()));
  }
}
