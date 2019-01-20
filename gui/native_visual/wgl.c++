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

#include "gui/native_visual/wgl.h++"

#include <core/debug.h++>
#include <core/library.h++>

namespace skui::gui::native_visual
{
  namespace
  {
    base::gl_function_type get_gl(void*, const char name[])
    {
      static core::library lib("opengl32.dll");

      static const bool load_libopengl_success = lib.load();
      if(!load_libopengl_success)
        core::debug_print("Failed to load opengl32.dll.\n");

      return lib.resolve<void()>(name);
    }
  }

  wgl::wgl() = default;

  wgl::~wgl() = default;

  void wgl::create_surface(std::uintptr_t window)
  {
    HWND handle = reinterpret_cast<HWND>(window);
    device_context = GetDC(handle);

    static const PIXELFORMATDESCRIPTOR pixel_format_descriptor
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

    int pixel_format = ChoosePixelFormat(device_context, &pixel_format_descriptor);
    if(pixel_format == 0)
      core::debug_print("Failed choosing pixel format.\n");

    BOOL success = SetPixelFormat(device_context, pixel_format, &pixel_format_descriptor);
    if(success == FALSE)
      core::debug_print("Failed setting pixel format.\n");

    gl_context = wglCreateContext(device_context);
    if(!gl_context)
      core::debug_print("Failed creating WGL Context.\n");
  }

  void wgl::swap_buffers(const graphics::pixel_size&) const
  {
    if(SwapBuffers(device_context) != TRUE)
      core::debug_print("Call to SwapBuffers failed.\n");
  }

  void wgl::make_current() const
  {
    BOOL success = wglMakeCurrent(device_context, gl_context);
    if(success == FALSE)
      core::debug_print("Failed making WGL Context current.\n");
  }

  base::gl_get_function_type wgl::get_gl_function() const
  {
    return &get_gl;
  }
}
