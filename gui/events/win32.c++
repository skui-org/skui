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

#include "gui/events/win32.h++"

#include "gui/native_window/win32.h++"
#include "gui/window.h++"

#include <core/debug.h++>
#include <core/utility.h++>

namespace skui::gui::events
{
  win32::win32(gui::window& window)
    : base{window}
  {}

  win32::~win32() = default;

  void skui::gui::events::win32::exec()
  {
    auto win32_window = dynamic_cast<native_window::win32*>(&window.get_native_window());
    if(!win32_window)
      core::debug_print("events::win32 only functions with native_window::win32.\n");

    HWND hwnd = win32_window->get_hwnd();

    // embed a pointer to this so we can e.g. repaint ourselves
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));

    MSG message;
    BOOL result;
    while((result = GetMessageW(&message, hwnd, 0, 0)) >= 0)
    {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    core::debug_print("exited event loop.\n");
  }
}
