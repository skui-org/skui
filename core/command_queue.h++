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

/*
 * Thread-safe, waitable queue of commands.
 */

#ifndef SKUI_CORE_COMMAND_QUEUE_H
#define SKUI_CORE_COMMAND_QUEUE_H

#include "core/command.h++"

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

namespace skui::core
{
  class command_queue
  {
  public:
    using command_ptr = std::unique_ptr<command>;
    using commands_type = std::deque<command_ptr>;

    command_queue(commands_type commands = {});

    void push(command_ptr&& command);
    void push_front(command_ptr&& command);

    //! \note returns immediately if there are unprocessed commands in the queue.
    void wait();

    commands_type take_commands();

  private:
    std::mutex queue_mutex;
    std::condition_variable condition_variable;
    commands_type queue;
  };
}

#endif
