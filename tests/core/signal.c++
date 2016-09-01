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
  using skui::test::assert;

  namespace
  {
    bool free_slot_called = false;
    void slot() { free_slot_called = true; }

    bool overloaded_slot_called = false;
    void slot(bool) { overloaded_slot_called = true; }

    void test_signal_connect_emit()
    {

      bool lambda_slot_called = false;
      auto lambda_slot = [&lambda_slot_called]() { lambda_slot_called = true; };

      skui::core::signal<> signal;
      signal.connect(static_cast<void(*)()>(slot));
      signal.connect(lambda_slot);

      signal.emit();
      assert(free_slot_called, "free function slot called.\n");
      assert(lambda_slot_called, "lambda function slot called.\n");
      assert(!overloaded_slot_called, "overloaded slot not called.\n");
    }
  }

  void test_basic_operations()
  {
    bool slot_called = false;
    auto slot = [&slot_called]() { slot_called = true; };
    skui::core::signal<> signal_one;
    skui::core::signal<> signal_two;

    signal_one.connect(slot);

    signal_two = signal_one;

    signal_one.emit();

    assert(slot_called, "Copied-from signal still connected.");

    slot_called = false;

    signal_two.emit();

    assert(slot_called, "Copied-to signal connected.");

    signal_two = std::move(signal_one);
    slot_called = false;

    signal_one.emit();

    assert(!slot_called, "Moved-from signal disconnected.");

    signal_two.emit();

    assert(slot_called, "moved-to signal connected correclty.");
  }

  void test_signal_with_argument()
  {
    bool slot_called = false;
    auto slot = [&slot_called](bool called) { slot_called = called; };

    skui::core::signal<bool> signal;
    signal.connect(slot);

    signal.emit(true);

    assert(slot_called, "Argument not passed through signal.");
  }

  void test_signal_disconnect()
  {
    bool slot_called = false;
    bool other_slot_called = false;
    auto slot = [&slot_called]() { slot_called = true; };
    auto other_slot = [&other_slot_called]() { other_slot_called = true; };

    skui::core::signal<> signal;
    signal.connect(slot);
    signal.connect(other_slot);
    signal.disconnect(slot);

    signal.emit();
    skui::test::assert(!slot_called, "Slot disconnected.");
    skui::test::assert(other_slot_called, "Other slot still connected.");

    signal.disconnect_all();

    other_slot_called = false;
    signal.emit();

    skui::test::assert(!other_slot_called, "Disconnect all slots.");
  }

  struct mock
  {
    mock(){};
    void f() const volatile { slot_called = true; };
    void g(int);
    mutable bool slot_called = false;
  };

  void test_member_functions()
  {
    mock object;
    {
      skui::core::signal<> signal;
      signal.connect(&object, &mock::f);
      signal.emit();

      assert(object.slot_called, "member function slot called.");
    }
    {
      const mock other_object;
      skui::core::signal<> signal;
      signal.connect(&object, &mock::f);
      signal.connect(&other_object, &mock::f);
      signal.disconnect(&other_object);

      signal.emit();
      assert(object.slot_called, "connected slot called");
      assert(!other_object.slot_called, "disconnected slot called");
    }
    {
      const volatile mock cv_object;
      skui::core::signal<> signal;
      signal.connect(&cv_object, &mock::f);

      signal.emit();
      assert(cv_object.slot_called, "const volatile object connected");
    }
  }
}

int main()
{
  test_signal_connect_emit();
  test_basic_operations();
  test_signal_with_argument();
  test_signal_disconnect();
  test_member_functions();
}
