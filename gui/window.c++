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

#include "gui/window.h++"

#include "gui/element.h++"
#include "gui/events.h++"
#include "gui/native_visual/raster.h++"
#include "gui/native_window.h++"

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
      : trackable{}
      , size{initial_size}
      , position{position}
      , icon{}
      , title{[this](const core::string& title) { native_window->set_title(title); },
              [this] { return native_window->get_title(); }}
      , native_window{nullptr}
      , thread{}
      , flags{flags}
      , has_been_closed{false}
    {
      std::unique_lock lock{mutex};
      std::thread t(&window::initialize_and_execute_platform_loop, this);
      thread.swap(t);
      handle_condition_variable.wait(lock, [this] { return native_window != nullptr; });
      implementation::windows().push_back(this);

      title = core::application::instance().name;
    }

    window::window(window_flags flags)
      : window({0,0}, {800,600}, flags)
    {}

    window::~window()
    {
      core::debug_print("Destroying window.\n");
      if(native_window)
      {
        close();
      }
      thread.join();
    }

    void window::show()
    {
      std::unique_lock lock{mutex};

      core::debug_print("Showing window.\n");

      native_window->show();
      state = window_state::windowed;
    }

    void window::hide()
    {
      std::unique_lock lock{mutex};

      core::debug_print("Hiding window.\n");

      native_window->hide();
      state = window_state::hidden;
    }

    void window::close()
    {
      std::unique_lock lock{mutex};

      core::debug_print("window::close called.\n");

      native_window->close();
      has_been_closed = true;
      window::windows().erase(std::remove(windows().begin(), windows().end(), this), windows().end());
    }

    void window::repaint(bool force)
    {
      std::unique_lock lock{mutex};

      if(has_been_closed)
        return;

      bool size_changed = false;
      auto size_changed_connection = size.value_changed.connect([&size_changed]() { size_changed = true; });
      std::tie(position, size) = native_window->get_current_geometry();
      size.value_changed.disconnect(size_changed_connection);

      if(size_changed || force)
      {
        native_window->make_current();

        draw();

        native_window->swap_buffers(size);
      }
    }

    native_window::base& window::get_native_window() const
    {
      return *native_window;
    }

    void window::draw()
    {
      graphics::canvas_flags canvas_flags;
      if(flags.test(window_flag::anti_alias))
        canvas_flags |= graphics::canvas_flag::anti_alias;

      auto canvas = graphics_context->create_canvas(size, canvas_flags);
      canvas->draw(canvas->background);

      element->draw(*canvas, {.5, .5}); // half pixel offset so line (1,1)---(1,10) lies on exactly one pixel line
    }

    void window::initialize_and_execute_platform_loop()
    {
      native_window = native_window::create(position, size, flags);

      create_graphics_context();

      // Ensure calling thread is waiting for draw_condition_variable
      std::unique_lock handle_lock{mutex};
      handle_condition_variable.notify_one();

      // Continue calling thread before initiating event loop
      handle_lock.unlock();

      execute_event_loop();

      graphics_context.reset();
      native_window.reset();

      if(flags.test(window_flag::exit_on_close))
        core::application::instance().quit();
    }

    void window::create_graphics_context()
    {
      if(flags.test(window_flag::opengl))
      {
        const auto& native_visual = native_window->get_native_visual();
        native_visual.make_current();
        graphics_context = std::make_unique<graphics::skia_gl_context>(native_visual.get_gl_function());
      }
      else
      {
        auto raster_visual = dynamic_cast<native_visual::raster*>(&native_window->get_native_visual());
        if(!raster_visual)
          core::debug_print("In case of non-OpenGL, the visual must be a raster visual");

        graphics_context = std::make_unique<graphics::skia_raster_context>(raster_visual->pixels());
      }
    }

    void window::execute_event_loop()
    {
      std::unique_ptr<events::base> events = events::create(*this);

      events->exec();
    }

    window::window_list& window::windows()
    {
      return implementation::windows();
    }
  }
}
