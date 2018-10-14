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

#include "gui/native_visual/cgl.h++"

#include <core/library.h++>

namespace skui::gui::native_visual
{
  namespace
  {
    base::gl_function_type cgl_get(void*, const char name[])
    {
      static core::library libgl("/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib");

      libgl.load();

      return libgl.resolve<void>(name);
    }
  }
  cgl::cgl() = default;

  cgl::~cgl() = default;

  void cgl::create_surface(std::uintptr_t)
  {}

  void cgl::make_current() const
  {}

  void cgl::swap_buffers(const graphics::pixel_size&) const
  {}

  base::gl_get_function_type cgl::get_gl_function() const
  {
    return &cgl_get;
  }
}
