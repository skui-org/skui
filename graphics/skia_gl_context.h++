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

#ifndef SKUI_GRAPHICS_SKIA_GL_CONTEXT_H
#define SKUI_GRAPHICS_SKIA_GL_CONTEXT_H

#include "context.h++"

#include "size.h++"

#include <GrContext.h>
#include <GrGLInterface.h>

#include <memory>

class SkSurface;

namespace skui
{
  namespace graphics
  {
    class canvas;

    class skia_gl_context : public context
    {
    public:
      skia_gl_context();
      ~skia_gl_context() override = default;

      std::unique_ptr<canvas> create_canvas(const pixel_size& size) const override;

    private:
      sk_sp<const GrGLInterface> gr_gl_interface;
    };
  }
}

#endif
