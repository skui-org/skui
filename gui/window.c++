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

#include <core/application.h++>

#include <memory>
#include <vector>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
      // These are implemented in window_<platform>.c++
      extern platform_handle* initialize_platform_window(const pixel_position& position, const pixel_size& size);

      std::unique_ptr<window::window_list> list_of_windows;
      window::window_list& windows()
      {
        list_of_windows = std::make_unique<window::window_list>();

        return *list_of_windows;
      }
    }

    window::window(pixel_position position, pixel_size initial_size, core::bitflag<window_flags> flags)
      : trackable()
      , size{initial_size.width, initial_size.height}
      , maximum_size{}
      , minimum_size{}
      , position{position}
      , icon{}
      , title{}
      , flags(flags)
      , native_handle(nullptr)
      , thread()
    {
      std::unique_lock<decltype(handle_mutex)> lock(handle_mutex);
      std::thread t(&window::initialize_and_execute_platform_loop, this);
      thread.swap(t);
      handle_condition_variable.wait(lock, [this] { return native_handle != nullptr; });
      implementation::windows().push_back(this);
    }

    void window::draw()
    {
      glClearColor(1.0, 1.0, 1.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-1., 1., -1., 1., 1., 20.);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

      glBegin(GL_QUADS);
       glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
       glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
       glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
       glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
      glEnd();
    }

    window::window_list& window::windows()
    {
      return implementation::windows();
    }
  }
}
