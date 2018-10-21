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
 * Event loop
 * Simple event loop
 */

#ifndef SKUI_CORE_EVENT_LOOP_H
#define SKUI_CORE_EVENT_LOOP_H

#include "core/command_queue.h++"

#include <atomic>

namespace skui::core
{
  class event_loop
  {
  public:
    using filter_type = std::function<void(command_queue::commands_type&)>;
    event_loop(filter_type filter,
               command_queue::commands_type commands = {});
    event_loop(command_queue::commands_type commands = {});

    int execute();

    void push(command_queue::command_ptr&& command);

    void stop(int return_code = 0);
    void interrupt(int return_code = 0);

    filter_type filter;

  private:
    command_queue queue;
    bool exit {false};
    int exit_code {0};
  };
}

#endif
