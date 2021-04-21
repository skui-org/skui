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

#include "gui/native_visual/win32.h++"

#include <core/debug.h++>

namespace skui::gui::native_visual
{
  namespace
  {
    BITMAPINFO create_bitmapinfo(const graphics::pixel_size& size)
    {
      BITMAPINFO bitmap_info{};
      bitmap_info.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
      bitmap_info.bmiHeader.biWidth       = static_cast<LONG>(size.width);
      bitmap_info.bmiHeader.biHeight      = -static_cast<LONG>(size.height); // top-down image
      bitmap_info.bmiHeader.biPlanes      = 1;
      bitmap_info.bmiHeader.biBitCount    = 32;
      bitmap_info.bmiHeader.biCompression = BI_RGB;
      bitmap_info.bmiHeader.biSizeImage   = 0;

      return bitmap_info;
    }
  }
  win32::win32() = default;

  win32::~win32() = default;

  void win32::create_surface(std::uintptr_t window)
  {
    HWND hwnd = reinterpret_cast<HWND>(window);
    device_context = GetDC(hwnd);
  }

  void win32::make_current() const
  {

  }

  void win32::make_no_current() const
  {

  }

  void win32::swap_buffers(const graphics::pixel_size& size) const
  {
    BITMAPINFO bitmap_info = create_bitmapinfo(size);

    int ret = SetDIBitsToDevice(device_context,
                                0, 0,
                                static_cast<DWORD>(size.width), static_cast<DWORD>(size.height),
                                0, 0,
                                0, static_cast<UINT>(size.height),
                                pixels().data(),
                                &bitmap_info,
                                DIB_RGB_COLORS);
    if(ret == 0)
      core::debug_print("SetDIBitsToDevice failed.\n");
  }
}
