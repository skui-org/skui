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

#include "gui/window.h++"

#include <core/application.h++>
#include <core/debug.h++>

#include <graphics/context.h++>
#include <graphics/context.h++>

#include <memory>
#include <vector>

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
      // These are implemented in window_<platform>.c++
      extern platform_handle* initialize_platform_window(const graphics::pixel_position& position,
                                                         const graphics::pixel_size& size);

      static std::unique_ptr<window::window_list> list_of_windows;
      window::window_list& windows()
      {
        list_of_windows = std::make_unique<window::window_list>();

        return *list_of_windows;
      }
    }

    window::window(graphics::pixel_position position,
                   graphics::pixel_size initial_size,
                   window_flags flags)
      : trackable()
      , size{initial_size.width, initial_size.height}
      , maximum_size{}
      , minimum_size{}
      , position{position}
      , icon{}
      , title([this](const core::string& title) { set_title(title); },
              [this] { return get_title(); })
      , native_handle(nullptr)
      , thread()
      , flags(flags)
    {
      std::unique_lock<decltype(handle_mutex)> lock(handle_mutex);
      std::thread t(&window::initialize_and_execute_platform_loop, this);
      thread.swap(t);
      handle_condition_variable.wait(lock, [this] { return native_handle != nullptr; });
      implementation::windows().push_back(this);

      title = core::application::instance().name;
    }

    window::~window()
    {
      core::debug_print("Destroying window.\n");
      if(native_handle)
      {
        close();
      }
      thread.join();
    }

    void window::draw()
    {
      auto canvas = graphics_context->create_canvas(size);
      canvas->draw();
    }

    window::window_list& window::windows()
    {
      return implementation::windows();
    }
  }
}
