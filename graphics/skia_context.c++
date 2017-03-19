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

#include "skia_context.h++"

#include "skia_canvas.h++"

#include <core/debug.h++>

#include <gl/GrGLInterface.h>

#include <thread>

namespace skui
{
  namespace graphics
  {
    skia_context::skia_context()
      : context()
      , gr_gl_interface(GrGLCreateNativeInterface())
    {
      core::debug_print("skia_context thread: ", std::this_thread::get_id(), '\n');
      SkASSERT(gr_gl_interface);
    }

    std::unique_ptr<canvas> skia_context::create_canvas(const pixel_size& size) const
    {
      return std::make_unique<skia_canvas>(size, *gr_gl_interface, canvas_flag::anti_alias);
    }
  }
}
