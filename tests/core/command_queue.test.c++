/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

#include "test.h++"

#include <core/command_queue.h++>

#include <thread>

namespace
{
  using skui::test::check;

  struct fixture
  {
    bool command_executed = false;
    void f() { command_executed = true; }

    void test_command_queue_construct_take()
    {
      skui::core::command_queue::commands_type initial_commands;
      initial_commands.push_back(std::make_unique<skui::core::command>([this] { f(); }));
      skui::core::command_queue command_queue{std::move(initial_commands)};

      auto commands = command_queue.take_commands();

      check(commands.size() == 1, "Commands given at construction time inserted correctly.");

      commands.front()->execute();
      check(command_executed, "commands from construction time correctly executed.");
    }

    void test_command_queue_push_take()
    {
      skui::core::command_queue command_queue;

      command_queue.push(std::make_unique<skui::core::command>([this] { f(); }));

      auto commands = command_queue.take_commands();
      check(commands.size() == 1, "Commands pushed and taken correctly.");

      commands.front()->execute();
      check(command_executed, "Taken command correctly executed.");

      commands = command_queue.take_commands();
      check(commands.empty(), "Taking commands empties command_queue.");
    }

    void test_command_queue_push_front_take()
    {
      skui::core::command_queue command_queue;

      command_queue.push(std::make_unique<skui::core::command>([this] { f(); }));
      command_queue.push_front(std::make_unique<skui::core::command>([] {}));

      auto commands = command_queue.take_commands();

      commands.front()->execute();

      check(!command_executed, "push_front inserts in front of previously inserted commands.");
    }

    void f_wait(skui::core::command_queue* queue, std::mutex* mutex, std::condition_variable* cv, bool* should_wakeup)
    {
      std::unique_lock lock{*mutex};

      queue->wait();

      check(*should_wakeup == false, "queue doesn't execute command on wait.");

      auto commands = queue->take_commands();

      check(commands.size() == 1, "Command pushed to queue.");

      commands.front()->execute();

      cv->notify_one();
    }

    void test_command_queue_wait()
    {
      skui::core::command_queue command_queue;
      std::mutex mutex;
      std::condition_variable cv;
      bool should_wakeup = false;

      std::unique_lock lock{mutex};

      std::thread thread(&fixture::f_wait, this, &command_queue, &mutex, &cv, &should_wakeup);

      command_queue.push(std::make_unique<skui::core::command>([&should_wakeup] { should_wakeup = true; }));

      cv.wait(lock, [&should_wakeup] { return should_wakeup; });

      thread.join();
    }
  };
}

int main()
{
  fixture{}.test_command_queue_construct_take();
  fixture{}.test_command_queue_push_take();
  fixture{}.test_command_queue_push_front_take();
  fixture{}.test_command_queue_wait();

  return skui::test::exit_code;
}
