/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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

#include "opengl/functions.h++"

#include "opengl/function_type.h++"
#include "opengl/function_name.h++"

#include <core/debug.h++>
#include <core/path.h++>
#include <core/library.h++>

namespace skui::graphics::opengl
{
  namespace
  {
    using namespace std::literals::string_literals;

    const core::string libgl_name =
    #if defined(_WIN32) || defined(__APPLE__)
        "OpenGL"s;
#else
        "GL"s;
#endif
    const core::string libegl_name = "EGL"s;


  }
  functions::functions(opengl::version version)
    : version{version}
    , function_pointers{static_cast<std::size_t>(function::last)}
  {
    if(version >= opengl::version::gl_es_1_0)
      initialize_gl_es();
    else
      initialize_gl();
  }

  void functions::initialize_gl()
  {
    core::library libgl(libgl_name);

    if(libgl.load())
    {
      for(std::size_t i = 0; i<function_pointers.size(); ++i)
      {
        function_pointers[i] = libgl.resolve<void()>(opengl::name[i]);
        if(function_pointers[i] != nullptr)
        {
          core::debug_print("succesfully loaded ", opengl::name[i]);
        }
      }
    }
    else
      core::debug_print("Failed to load OpenGL library.\n");
  }

  void functions::initialize_gl_es()
  {

  }
}
