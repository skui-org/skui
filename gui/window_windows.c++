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

#ifndef UNICODE
#define UNICODE
#endif
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <windows.h>
#include <GL/gl.h>

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
        wc.hIcon         = LoadIcon(application_instance, (LPCWSTR)IDI_WINLOGO);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
        wc.lpszMenuName  = L"Skui menu";
        wc.lpszClassName = window_class;
        wc.hIconSm       = LoadIcon(application_instance, (LPCWSTR)IDI_WINLOGO);

        return RegisterClassExW(&wc);
      }

      HWND initialize()
      {
        const static bool registered = register_window_class();

        return CreateWindowExW(
              WS_EX_CLIENTEDGE,
              window_class,
              L"A Skui Window",
              WS_OVERLAPPEDWINDOW,
              CW_USEDEFAULT, CW_USEDEFAULT,
              CW_USEDEFAULT, CW_USEDEFAULT,
              nullptr, nullptr,
              application_instance, nullptr
              );

      }
    }


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
      ShowWindow(static_cast<HWND>(native_handle), SW_SHOWNORMAL);
    }

    void window::hide()
    {
      ShowWindow(static_cast<HWND>(native_handle), SW_HIDE);
    }





/*

      HDC hdc = GetDC(native_handle);

      skia_gl_context = SkCreateWGLContext(hdc,
                                           0,
                                           true,
                                           kGLPreferCompatibilityProfile_SkWGLContextRequest);

      glClearStencil(0);
      glClearColor(0, 0, 0, 0);
      glStencilMask(0xffffffff);
      glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
      if(wglMakeCurrent(hdc, skia_gl_context))
      {
        // use DescribePixelFormat to get the stencil and color bit depth.
        int pixelFormat = GetPixelFormat(hdc);
        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormath(hdc, pixelFormat, sizeof(pfd), &pfd);
        info->fStencilBits = pfd.cStencilBits;
        // pfd.cColorBits includes alpha, so it will be 32 in 8/8/8/8 and 10/10/10/2
        info->fColorBits = pfd.cRedBits + pfd.cGreenBits + pfd.cBlueBits;

        // Get sample count if the MSAA WGL extension is present
        SkWGLExtensions extensions;
        if (extensions.hasExtension(dc, "WGL_ARB_multisample")) {
          static const int kSampleCountAttr = SK_WGL_SAMPLES;
          extensions.getPixelFormatAttribiv(dc,
                                            pixelFormat,
                                            0,
                                            1,
                                            &kSampleCountAttr,
                                            &info->fSampleCount);

                  return native_handle;
        }
        */
  }
}
