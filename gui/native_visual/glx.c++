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

#include "gui/native_visual/glx.h++"

#include <core/debug.h++>

#include <GL/glx.h>

#include <cstring>

namespace skui
{
  namespace gui
  {
    namespace native_visual
    {
      namespace
      {
        base::gl_function_type glx_get(void*, const char name[])
        {
          // Avoid calling glXGetProcAddress() for EGL procs.
          // We don't expect it to ever succeed, but somtimes it returns non-null anyway.
          if (0 == std::strncmp(name, "egl", 3)) {
              return nullptr;
          }

          return glXGetProcAddress(reinterpret_cast<const GLubyte*>(name));
        }
      }
      glx::glx(Display* display)
        : display(display)
        , xvisualinfo(create_xvisualinfo())
        , context(glXCreateContext(display, xvisualinfo, nullptr, True))
        , drawable(0)
      {}

      void glx::create_surface(std::uintptr_t drawable)
      {
        // The surface is the window itself
        this->drawable = static_cast<Window>(drawable);
      }

      glx::~glx() = default;

      void glx::make_current() const
      {
        if(glXMakeCurrent(display, drawable, context) == False)
          core::debug_print("Call to glXMakeCurrent failed.\n");
      }

      void glx::swap_buffers(const graphics::pixel_size&) const
      {
        glXSwapBuffers(display, drawable);
      }

      base::gl_get_function_type glx::get_gl_function() const
      {
        return &glx_get;
      }

      XVisualInfo* glx::get_xvisualinfo() const
      {
        return xvisualinfo;
      }

      XVisualInfo* glx::create_xvisualinfo()
      {
        static int attributes[]
        {
          GLX_RGBA,
          GLX_DEPTH_SIZE, 24,
          GLX_DOUBLEBUFFER,
          None
        };
        const int default_screen = DefaultScreen(display);
        return glXChooseVisual(display, default_screen, attributes);
      }
    }
  }
}
