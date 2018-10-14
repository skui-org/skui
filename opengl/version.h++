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

/*
 * OpenGL API versions.
 */

#ifndef SKUI_OPENGL_VERSION_H
#define SKUI_OPENGL_VERSION_H

#include <core/bitflag.h++>

namespace skui::graphics::opengl
{
  enum class version
  {
    // Ancient versions
    gl_1_0, gl_1_1, gl_1_2, gl_1_2_1,
    gl_1_3, gl_1_4, gl_1_5,
    gl_2_0, gl_2_1,

    // "new" OpenGL versions
    gl_3_0, gl_3_1,
    gl_3_2_core,
    gl_3_2_compatibility,
    gl_3_3_core,
    gl_3_3_compatiblity,
    gl_4_0_core,
    gl_4_0_compatibility,
    gl_4_1_core,
    gl_4_1_compatibility,
    gl_4_2_core,
    gl_4_2_compatibility,
    gl_4_3_core,
    gl_4_3_compatibility,
    gl_4_4_core,
    gl_4_4_compatibility,
    gl_4_5_core,
    gl_4_5_compatibility,

    // OpenGL|ES versions
    gl_es_1_0, gl_es_1_1,
    gl_es_2_0,
    gl_es_3_0, gl_es_3_1, gl_es_3_2
  };

  using version_flags = core::bitflag<version>;
  using namespace core::bitflag_operators;
}

#endif
