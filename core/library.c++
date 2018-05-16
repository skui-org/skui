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

#include "core/library.h++"

namespace skui
{
  namespace core
  {
    namespace implementation
    {
      // these are defined in library_*.c++
      void* load(const path& library);
      bool unload(void*);
    }
    library::library(path filename)
      : filename{std::move(filename)}
      , native_handle{nullptr}
    {}

    library::~library()
    {
      unload();
    }

    bool library::load(path filename_to_load)
    {
      if(filename == filename_to_load)
      {
        if(native_handle)
          return true;
      }
      else
      {
        if(!filename_to_load.empty())
          filename = std::move(filename_to_load);
      }
      native_handle = implementation::load(filename.c_str());

      return native_handle != nullptr;
    }

    bool library::unload()
    {
      bool result = true;
      if(native_handle != nullptr)
        result = implementation::unload(native_handle);

      native_handle = nullptr;

      return result;
    }
  }
}
