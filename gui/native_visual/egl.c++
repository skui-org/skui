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

#include "gui/native_visual/egl.h++"

#include <core/debug.h++>

#include <cstring>

namespace skui::gui::native_visual
{
  namespace
  {
    base::gl_function_type egl_get(void*, const char name[])
    {
      base::gl_function_type ptr = eglGetProcAddress(name);
      if(!ptr)
      {
        if(0 == std::strcmp("eglQueryString", name))
          return reinterpret_cast<base::gl_function_type>(eglQueryString);
        else if(0 == std::strcmp("eglGetCurrentDisplay", name))
          return reinterpret_cast<base::gl_function_type>(eglGetCurrentDisplay);
      }
      return ptr;
    }
  }

  egl::egl()
    : egl_display{eglGetDisplay(EGL_DEFAULT_DISPLAY)}
  {
    if(egl_display == EGL_NO_DISPLAY)
      core::debug_print("Call to eglGetDisplay failed.\n");

    if(EGL_FALSE == eglInitialize(egl_display, nullptr, nullptr))
      core::debug_print("Call to eglInitialize failed.\n");
  }

  egl::~egl()
  {
    if(egl_context)
    {
      eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      eglDestroyContext(egl_display, egl_context);
    }
    if(egl_surface)
      eglDestroySurface(egl_display, egl_surface);
    if(egl_display)
      eglTerminate(egl_display);
  }

  void egl::create_surface(std::uintptr_t window)
  {
    egl_surface = eglCreateWindowSurface(egl_display,
                                         egl_config,
                                         reinterpret_cast<EGLNativeWindowType>(window),
                                         nullptr);

    eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
  }

  void egl::make_current() const
  {
    eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
  }

  void egl::swap_buffers(const graphics::pixel_size&) const
  {
    eglSwapBuffers(egl_display, egl_surface);
  }

  EGLint egl::get_egl_visual()
  {
    if(EGL_FALSE == eglBindAPI(EGL_OPENGL_API))
      core::debug_print("Call to eglBindAPI failed.\n");

    static const EGLint attribute_list[]
    {
      EGL_RED_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_BLUE_SIZE, 8,
          EGL_ALPHA_SIZE, 8,
          EGL_NONE
    };

    EGLint num_config;
    if(EGL_FALSE == eglChooseConfig(egl_display, attribute_list, &egl_config, 1, &num_config))
      core::debug_print("Call to eglChooseConfig failed.\n");

    static const EGLint context_attributes[]
    {
      EGL_NONE
    };

    egl_context = eglCreateContext(egl_display, egl_config, EGL_NO_CONTEXT, context_attributes);
    if(egl_context == EGL_NO_CONTEXT)
      core::debug_print("Call to eglCreateContext failed.\n");

    //Request eglVisualID for native window
    EGLint egl_native_visualid;
    if(EGL_FALSE == eglGetConfigAttrib(egl_display, egl_config, EGL_NATIVE_VISUAL_ID, &egl_native_visualid))
      core::debug_print("Call to eglGetConfigAttrib failed\n");

    return egl_native_visualid;
  }

  base::gl_get_function_type egl::get_gl_function() const
  {
    return &egl_get;
  }
}
