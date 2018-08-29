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

#include "core/command_queue.h++"

namespace skui
{
  namespace core
  {
    void command_queue::push(command_ptr&& command)
    {
      const std::lock_guard lock{queue_mutex};

      queue.push_back(std::move(command));
      condition_variable.notify_one();
    }

    void command_queue::push_front(command_queue::command_ptr&& command)
    {
      std::lock_guard lock{queue_mutex};

      queue.push_front(std::move(command));
      condition_variable.notify_one();
    }

    void command_queue::wait()
    {
      std::unique_lock lock{queue_mutex};

      if(queue.empty())
        condition_variable.wait(lock, [this] { return !queue.empty(); });
    }

    std::deque<command_queue::command_ptr> command_queue::take_commands()
    {
      const std::lock_guard lock{queue_mutex};

      std::deque<command_queue::command_ptr> result;
      std::swap(result, queue);

      return result;
    }
  }
}
