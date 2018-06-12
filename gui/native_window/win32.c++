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

#include "gui/native_window/win32.h++"

#include "gui/events/win32.h++"

#include <core/debug.h++>
#include <core/utility.h++>

namespace skui
{
  namespace gui
  {
    namespace native_window
    {
      namespace
      {
        static const HINSTANCE application_instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));

        constexpr wchar_t window_class[] = L"skui window";

        bool register_window_class()
        {
          WNDCLASSEXW wc;

          // Register the Window Class
          wc.cbSize        = sizeof(WNDCLASSEXW);
          wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
          wc.lpfnWndProc   = events::win32::window_procedure;
          wc.cbClsExtra    = 0;
          wc.cbWndExtra    = 0;
          wc.hInstance     = application_instance;
          wc.hIcon         = LoadIconW(application_instance, (LPCWSTR)IDI_WINLOGO);
          wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
          wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
          wc.lpszMenuName  = L"Skui menu";
          wc.lpszClassName = window_class;
          wc.hIconSm       = LoadIconW(application_instance, (LPCWSTR)IDI_WINLOGO);

          return RegisterClassExW(&wc) == 0;
        }
      }
      win32::win32(std::unique_ptr<native_visual::base> native_visual)
        : base{std::move(native_visual)}
        , window{nullptr}
      {
        const static bool dummy = register_window_class();
        if(!dummy)
        {
          core::debug_print("Call to RegisterClassExW failed.\n", core::get_last_error_string());
        }
      }

      win32::~win32() = default;

      void win32::create(const skui::graphics::pixel_position& initial_position,
                         const skui::graphics::pixel_size& initial_size)
      {
        window = CreateWindowExW(WS_EX_CLIENTEDGE,
                                 window_class,
                                 L"A Skui Window",
                                 WS_OVERLAPPEDWINDOW,
                                 static_cast<int>(initial_position.x), static_cast<int>(initial_position.y),
                                 static_cast<int>(initial_size.width), static_cast<int>(initial_size.height),
                                 nullptr, nullptr,
                                 application_instance, nullptr
                                 );
        if(!window)
          core::debug_print("Call to CreateWindowExW failed.\n", core::get_last_error_string());

        native_visual->create_surface(reinterpret_cast<std::uintptr_t>(window));
      }

      void win32::show()
      {
        ShowWindowAsync(window, SW_SHOWNORMAL);
      }

      void win32::hide()
      {
        ShowWindowAsync(window, SW_HIDE);
      }

      void win32::close()
      {
        CloseWindow(window);
      }

      skui::core::string win32::get_title() const
      {
        int length = GetWindowTextLengthW(window);
        std::wstring title;
        title.resize(static_cast<std::size_t>(length)+1);
        GetWindowTextW(window, &title[0], length);
        return core::convert_to_utf8(title);
      }

      void win32::set_title(const skui::core::string& title)
      {
        SetWindowTextW(window, core::convert_to_utf16(title).c_str());
      }

      std::pair<graphics::pixel_position, graphics::pixel_size> win32::get_current_geometry() const
      {
        RECT rect;
        GetClientRect(window, &rect);

        return {{static_cast<std::int32_t>(rect.left), static_cast<std::int32_t>(rect.top)},
                {static_cast<graphics::pixel>(rect.right-rect.left), static_cast<graphics::pixel>(rect.bottom - rect.top)}};
      }

      HWND win32::get_hwnd() const
      {
        return window;
      }
    }
  }
}

