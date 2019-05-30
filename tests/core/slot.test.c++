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

#include "core/slot.h++"

namespace
{
  using skui::test::check;

  int f_called = 0;
  void f() { f_called++; }
  void f_arg(int i) { f_called = i; }

  int l_called = 0;
  const auto l = [] { l_called++; };
  const auto l_arg = [](int i) { l_called = i; };

  int f_return() { return 42; }
  const auto l_return = [] { return 43; };

  struct mock
  {
    void m() { called = 1; }
    void m() const { const_called = 11; }
    void m_arg(int i) { called = i; }
    void m_arg(int i) const { const_called = i; }
    int m_return() { return 44; }
    int m_return() const { return 33; }
    int called = 0;
    mutable int const_called = 0;
  };

  void test_callable_slot()
  {
    {
      skui::core::slot<void> slot(&f);
      slot();
      check(f_called == 1, "function called through slot.");

      skui::core::slot<void, int> slot_arg(&f_arg);
      slot_arg(2);
      check(f_called == 2, "function with argument called through slot.");

      skui::core::slot<void, int> slot_arg_less(&f);
      slot_arg_less(3);
      check(f_called == 3, "function called through slot extra arguments ignored.");
    }
    {
      skui::core::slot<void> slot(l);
      slot();
      check(l_called == 1, "lambda called through slot.");

      skui::core::slot<void> rvalue_slot{[&slot] { slot(); }};
      rvalue_slot();
      check(l_called == 2, "rvalue lambda slot called through slot.");

      skui::core::slot<void, int> slot_arg(l_arg);
      slot_arg(1);
      check(l_called == 1, "lambda with argument called through slot.");

      skui::core::slot<void, int> slot_arg_less(l);
      slot_arg_less(3);
      check(l_called == 2, "lambda called through slot extra arguments ignored.");
    }
    {
      int captured = 0;
      const auto cl = [&captured](int i) { captured = i; };

      skui::core::slot<void, int> slot(cl);
      slot(1);
      check(captured == 1, "Capturing lambda slot called.");
    }
  }

  void test_member_slot()
  {
    {
      mock object;

      skui::core::slot<void> slot(&object, &mock::m);
      slot();
      check(object.called == 1, "member function called through slot.");

      skui::core::slot<void, int> slot_arg(&object, &mock::m_arg);
      slot_arg(2);
      check(object.called == 2, "member function with argument called through slot.");

      skui::core::slot<void, int> slot_arg_less(&object, &mock::m);
      slot_arg_less(3);
      check(object.called == 1, "member function called through slot extra arguments ignored.");
    }
    {
      const mock object;

      const skui::core::slot<void> slot(&object, &mock::m);
      slot();
      check(object.const_called == 11, "const member function called through slot.");

      const skui::core::slot<void, int> slot_arg(&object, &mock::m_arg);
      slot_arg(22);
      check(object.const_called == 22, "const member function with argument called through slot.");

      const skui::core::slot<void, int> slot_arg_less(&object, &mock::m);
      slot_arg_less(33);
      check(object.const_called == 11, "const member function called through slot extra arguments ignored.");
    }
  }

  void test_return_value_slot()
  {
    skui::core::slot<int> function_slot(&f_return);
    check(function_slot() == 42, "function slot returns correct return value.");

    skui::core::slot<int> lambda_slot(l_return);
    check(lambda_slot() == 43, "lambda slot returns correct return value.");

    skui::core::slot<int> rvalue_lambda_slot([&lambda_slot] {return lambda_slot(); });
    check(rvalue_lambda_slot() == 43, "rvalue lambda slot returns correct return value.");

    mock object;

    skui::core::slot<int> member_slot(&object, &mock::m_return);
    check(member_slot() == 44, "member slot returns correct return value.");

    skui::core::slot<int> const_member_slot(static_cast<const mock*>(&object), &mock::m_return);
    check(const_member_slot() == 33, "const member slot returns correct return value.");
  }
}

int main()
{
  test_callable_slot();
  test_member_slot();
  test_return_value_slot();

  return skui::test::exit_code;
}
