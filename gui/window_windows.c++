/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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

#include "gui/window.h++"

#include <core/application.h++>
#include <core/debug.h++>

#ifndef UNICODE
#define UNICODE
#endif
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>

namespace skui
{
  namespace gui
  {
    // Helper functions
    namespace
    {
      const HINSTANCE application_instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));

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

      constexpr wchar_t window_class[] = L"skui window";

      bool register_window_class()
      {
        WNDCLASSEXW wc;

        // Register the Window Class
        wc.cbSize        = sizeof(WNDCLASSEXW);
        wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc   = WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = application_instance;
        wc.hIcon         = LoadIconW(application_instance, (LPCWSTR)IDI_WINLOGO);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
        wc.lpszMenuName  = L"Skui menu";
        wc.lpszClassName = window_class;
        wc.hIconSm       = LoadIconW(application_instance, (LPCWSTR)IDI_WINLOGO);

        return RegisterClassExW(&wc) == 0;
      }
    }

    namespace implementation
    {
      class platform_handle
      {
      public:
        HWND window_handle;
        HDC device_context;
        HGLRC gl_context;
      };

      platform_handle_ptr create_handle()
      {
        const static bool registered = register_window_class();

        return platform_handle_ptr(new platform_handle);
      }

      void platform_handle_deleter::operator()(platform_handle* handle) const
      {
        delete handle;
      }
    }

    void window::show()
    {
      ShowWindow(native_handle->window_handle, SW_SHOWNORMAL);
    }

    void window::hide()
    {
      ShowWindow(native_handle->window_handle, SW_HIDE);
    }

    void window::close()
    {
      CloseWindow(native_handle->window_handle);
    }

    void window::choose_visual(implementation::platform_handle &handle)
    {
      if(flags.test(window_flag::opengl))
      {
        static const PIXELFORMATDESCRIPTOR pixel_format_descriptor =
        {
          sizeof(PIXELFORMATDESCRIPTOR),
          1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
          PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
          32,                        //Colordepth of the framebuffer.
          0, 0, 0, 0, 0, 0,
          0,
          0,
          0,
          0, 0, 0, 0,
          24,                        //Number of bits for the depthbuffer
          8,                        //Number of bits for the stencilbuffer
          0,                        //Number of Aux buffers in the framebuffer.
          PFD_MAIN_PLANE,
          0,
          0, 0, 0
        };

        int pixel_format = ChoosePixelFormat(handle.device_context, &pixel_format_descriptor);
        if(pixel_format == 0)
          core::debug_print("Failed choosing pixel format.\n");

        BOOL success = SetPixelFormat(handle.device_context, pixel_format, &pixel_format_descriptor);
        if(success == FALSE)
          core::debug_print("Failed setting pixel format.\n");
      }
    }

    void window::setup_window(implementation::platform_handle &handle)
    {
      handle.window_handle = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            window_class,
            L"A Skui Window",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr, nullptr,
            application_instance, nullptr
            );

      // embed a pointer to this so we can e.g. repaint ourselves
      SetWindowLongPtrW(handle.window_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

      handle.device_context = GetDC(handle.window_handle);
    }

    void window::setup_graphics_backend(implementation::platform_handle& handle)
    {
      if(flags.test(window_flag::opengl))
      {
        handle.gl_context = wglCreateContext(handle.device_context);
        if(handle.gl_context == nullptr)
          core::debug_print("Failed creating WGL Context.\n");

        BOOL success = wglMakeCurrent(handle.device_context, handle.gl_context);
        if(success == FALSE)
          core::debug_print("Failed making WGL Context current.\n");
      }
    }

    void window::execute_event_loop()
    {
      MSG message;
      BOOL result;
      while((result = GetMessageW(&message, native_handle->window_handle, 0, 0)) > 0)
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }

      core::debug_print("exited event loop.\n");

    }

    void window::update_geometry()
    {

    }

    void window::swap_buffers()
    {
      if(flags.test(window_flag::opengl))
      {
        if(SwapBuffers(native_handle->device_context) != TRUE)
          core::debug_print("Call to SwapBuffers failed.\n");
      }
    }

    void window::set_title(const core::string& title)
    {
      SetWindowTextW(native_handle->window_handle, core::convert_to_utf16(title).c_str());
    }

    core::string window::get_title() const
    {
      int length = GetWindowTextLengthW(native_handle->window_handle);
      std::wstring title;
      title.resize(length+1);
      GetWindowTextW(native_handle->window_handle, &title[0], length);
      return core::convert_to_utf8(title);
    }
  }
}
