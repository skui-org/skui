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

#include "graphics/skia_gl_context.h++"

#include "graphics/skia_gl_canvas.h++"

#include <core/debug.h++>

#include <gl/GrGLInterface.h>
#include <gl/GrGLAssembleInterface.h>

#ifdef _WIN32
#include <windows.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <GL/glext.h>

namespace skui
{
  namespace graphics
  {
    skia_gl_context::skia_gl_context(gr_gl_get_function get_function)
      : context()
      , gr_gl_interface(GrGLAssembleInterface(nullptr, get_function))
    {
      SkASSERT(gr_gl_interface);
      SkASSERT(get_function);
    }

    skia_gl_context::~skia_gl_context() = default;

    std::unique_ptr<canvas> skia_gl_context::create_canvas(const pixel_size& size,
                                                           canvas_flags flags) const
    {
      glViewport(0, 0, static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height));

      return std::make_unique<skia_gl_canvas>(size, *gr_gl_interface, flags);
    }
  }
}
