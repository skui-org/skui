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

#include "test.h++"

#include <core/command_queue.h++>

namespace
{
  using skui::test::assert;

  bool command_executed = false;
  void f() { command_executed = true; }

  void test_command_queue()
  {
    skui::core::command_queue command_queue;

    command_queue.push(std::make_unique<skui::core::command>(f));

    auto commands = command_queue.take_commands();
    assert(commands.size() == 1, "Commands pushed and taken correctly.");

    commands.front()->execute();
    assert(command_executed, "Taken command correctly executed.");

    commands = command_queue.take_commands();
    assert(commands.empty(), "Taking commands empties command_queue.");
  }
}

int main()
{
  test_command_queue();

  return skui::test::exit_code;
}
