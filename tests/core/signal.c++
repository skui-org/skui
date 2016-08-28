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

#include "core/signal.h++"

namespace
{
  using skui::core::signal;

  void test_basic_operations()
  {
    // TODO test copy/move assignment operators
  }

  void test_simple_signal()
  {
    bool slot_called = false;
    auto slot = [&slot_called]() { slot_called = true; };

    signal<> simple_signal;
    simple_signal.connect(slot);

    simple_signal.emit();

    skui::test::assert(slot_called, "Simple slot not called through emit.");
  }

  void test_signal_with_argument()
  {
    bool slot_called = false;
    auto slot = [&slot_called](bool called) { slot_called = called; };

    signal<bool> signal_with_argument;
    signal_with_argument.connect(slot);

    signal_with_argument.emit(true);

    skui::test::assert(slot_called, "Argument not passed through signal.");
  }

  void test_signal_disconnect()
  {
    bool slot_called = false;
    bool other_slot_called = false;
    auto slot = [&slot_called]() { slot_called = true; };
    auto other_slot = [&other_slot_called]() { other_slot_called = true; };

    signal<> signal;
    signal.connect(slot);
    signal.connect(other_slot);
    signal.disconnect(slot);

    signal.emit();

    skui::test::assert(!slot_called, "Slot not disconnected.");
    skui::test::assert(other_slot_called, "Other slot still connected.");

    signal.disconnect_all();

    other_slot_called = false;
    signal.emit();

    skui::test::assert(!other_slot_called, "Disconnect all failed.");
  }
}

int main()
{
  test_basic_operations();
  test_simple_signal();
  test_signal_with_argument();
  test_signal_disconnect();
}
