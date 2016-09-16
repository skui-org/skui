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

#include "window.h++"

#include <core/debug.h++>

namespace skui
{
  namespace gui
  {
    window::window(pixel_position position, pixel_size initial_size)
      : size{initial_size.width, initial_size.height}
      , maximum_size{}
      , minimum_size{}
      , position{position}
      , icon{}
      , title{}
      , native_handle(initialize())
    {
    }

    void window::show()
    {
      ShowWindow(native_handle, SW_SHOWNORMAL);
    }

    void window::hide()
    {

    }

    namespace
    {
      LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
      {
        switch(msg)
        {
          case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
          case WM_DESTROY:
            PostQuitMessage(0);
            break;
          default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
        }
        return 0;
      }
    }

    HWND window::initialize()
    {
      WNDCLASSEXW wc;
      const HINSTANCE appInstance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));

      //Step 1: Registering the Window Class
      wc.cbSize        = sizeof(WNDCLASSEXW);
      wc.style         = 0;
      wc.lpfnWndProc   = WndProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hInstance     = appInstance;
      wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
      wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
      wc.lpszMenuName  = NULL;
      wc.lpszClassName = L"skui window";
      wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

      if(!RegisterClassExW(&wc))
      {
        MessageBoxW(nullptr, L"Window Registration Failed!", L"Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return nullptr;
      }

      HWND native_handle = CreateWindowExW(
              WS_EX_CLIENTEDGE,
              wc.lpszClassName,
              L"A Skui Window",
              WS_OVERLAPPEDWINDOW,
              static_cast<int>(position.x), static_cast<int>(position.y),
              static_cast<int>(size.width), static_cast<int>(size.height),
              nullptr, nullptr,
              appInstance, nullptr
              );

      if(native_handle == nullptr)
      {
        MessageBoxW(nullptr, L"Window Creation Failed!", L"Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return nullptr;
      }

      return native_handle;
    }
  }
}
