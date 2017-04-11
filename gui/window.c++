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

#include <graphics/skia_gl_context.h++>
#include <graphics/skia_raster_context.h++>

#include <memory>
#include <vector>

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
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

    void window::initialize_and_execute_platform_loop()
    {
      native_handle = implementation::create_handle();
      auto& handle = *native_handle;

      choose_visual(handle);

      setup_window(handle);

      setup_graphics_backend(handle);

      create_graphics_context();

      // Ensure calling thread is waiting for draw_condition_variable
      std::unique_lock<decltype(handle_mutex)> handle_lock(handle_mutex);
      handle_condition_variable.notify_one();

      // Continue calling thread before initiating event loop
      handle_lock.unlock();

      execute_event_loop();

      graphics_context.reset();
      native_handle.reset();

      if(flags.test(window_flag::exit_on_close))
        core::application::instance().quit();
    }

    void window::create_graphics_context()
    {
      if(flags.test(window_flag::opengl))
        graphics_context = std::make_unique<graphics::skia_gl_context>();
      else
        graphics_context = std::make_unique<graphics::skia_raster_context>();
    }

    window::window_list& window::windows()
    {
      return implementation::windows();
    }
  }
}
