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

#include "core/slot.h++"

namespace
{
  using skui::test::assert;
  using skui::core::implementation::callable_slot;
  using skui::core::implementation::member_function_slot;


  int f_called = 0;
  void f() { f_called = 1; }
  void f_arg(int i) { f_called = i; }

  int l_called = 0;
  const auto l = []() { l_called = 1; };
  const auto l_arg = [](int i) { l_called = i; };

  struct mock
  {
    void m() { called = 1; }
    void m_arg(int i) { called = i; }
    int called = 0;
  };

  void test_callable_slot()
  {
    {
      callable_slot<decltype(&f)> slot(&f);
      slot(nullptr);
      assert(f_called == 1, "function called through slot.");

      callable_slot<decltype(&f_arg), int> slot_arg(&f_arg);
      slot_arg(nullptr, 2);
      assert(f_called == 2, "function with argument called through slot.");
    }
    {
      callable_slot<decltype(l)> slot(l);
      slot(nullptr);
      assert(l_called == 1, "lambda called through slot.");

      callable_slot<decltype(l_arg), int> slot_arg(l_arg);
      slot_arg(nullptr, 2);
      assert(l_called == 2, "lambda with argument called through slot.");
    }
  }

  void test_member_slot()
  {
    mock object;

    member_function_slot<mock> slot(&mock::m);
    slot(&object);
    assert(object.called == 1, "member function called through slot.");

    member_function_slot<mock, int> slot_arg(&mock::m_arg);
    slot_arg(&object, 2);
    assert(object.called == 2, "member function with argument called through slot.");
  }
}

int main()
{
  test_callable_slot();
  test_member_slot();

  return skui::test::exit_code;
}
