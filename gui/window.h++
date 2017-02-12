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

/*
 * Window abstraction.
 */

#ifndef SKUI_GUI_WINDOW_H
#define SKUI_GUI_WINDOW_H

#include "icon.h++"

#include <core/bitflag.h++>
#include <core/string.h++>
#include <core/trackable.h++>

#include <graphics/context.h++>
#include <graphics/position.h++>
#include <graphics/size.h++>

#include <condition_variable>
#include <thread>
#include <vector>

namespace skui
{
  namespace gui
  {
    namespace implementation
    {
      class platform_handle;
    }

    enum class window_flag
    {
      none,
      exit_on_close, // Quit application when last window with this flag set closes
    };
    using window_flags = core::bitflag<window_flag>;
    using namespace core::bitflag_operators;

    class window : public core::trackable
    {
    public:
      using window_list = std::vector<window*>;

      window(graphics::pixel_position position = {0, 0},
             graphics::pixel_size initial_size = {800, 600},
             window_flags flags = window_flag::exit_on_close | window_flag::opengl);
      virtual ~window();

      void show();
      void hide();
      void close();

      void draw();

      // Properties
      graphics::pixel_size size;
      graphics::pixel_size maximum_size;
      graphics::pixel_size minimum_size;

      graphics::pixel_position position;

      core::property<gui::icon> icon;
      core::property<core::string> title;

      // Signals
      core::signal<> closed;
      core::signal<> minimized;

    private:
      const implementation::platform_handle* native_handle;
      void initialize_and_execute_platform_loop();

      static window_list& windows();

      std::unique_ptr<graphics::context> graphics_context;

      std::mutex handle_mutex;
      std::condition_variable handle_condition_variable;
      std::thread thread;
      window_flags flags;
    };
  }
}

#endif
