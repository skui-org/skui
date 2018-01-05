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

#include "test.h++"

#include "core/value_ptr.h++"

namespace
{
  using skui::test::check;

  struct Base
  {
    Base() = default;
    virtual ~Base() = default;
    Base(const Base&) = default;
  };
  struct Derived : Base {};

  void test_smart_copy()
  {
    skui::core::smart_copy<Base> base_copy;
    skui::core::smart_copy<Derived> derived_copy;

    base_copy = derived_copy;

    check(base_copy.get_copy_function() == derived_copy.get_copy_function(), "");
  }

  void test_value_ptr_constructors_get()
  {
    {
      Derived* derived = new Derived;
      skui::core::value_ptr<Derived> derived_ptr(derived);

      check(derived_ptr.get() == derived, "constructor stores pointer");
    }
    {
      Derived* derived = new Derived;
      skui::core::value_ptr<Base> base_ptr(derived);

      check(base_ptr.get() == derived, "value_ptr<Base> correctly constructed from derived");
    }
  }

  void test_value_ptr_copy()
  {
    skui::core::value_ptr<Base, skui::core::smart_copy<Derived>> base_ptr(new Derived);

    skui::core::value_ptr<Base> base_ptr_copy(base_ptr);

    check(base_ptr.get() != nullptr, "copied-from value_ptr is not nullptr");
    check(base_ptr_copy.get() != nullptr, "copied-to value_ptr is not nullptr");
    check(base_ptr_copy.get() != base_ptr.get(), "value_ptr copy constructor copies");
    check(dynamic_cast<Derived*>(base_ptr_copy.get()) != nullptr, "value_ptr copy constructor maintains dynamic type");
  }

  void test_value_ptr_move()
  {
    skui::core::value_ptr<Base, skui::core::smart_copy<Derived>> base_ptr(new Derived);

    skui::core::value_ptr<Base> base_ptr_move = std::move(base_ptr);

    check(base_ptr.get() == nullptr, "moved-from value_ptr is nullptr");
    check(base_ptr_move.get() != nullptr, "moved-to value_ptr is not nullptr");
    check(dynamic_cast<Derived*>(base_ptr_move.get()) != nullptr, "value_ptr move maintains dynamic type");
  }

  void test_value_ptr_make_value()
  {
    skui::core::value_ptr<Base> ptr = skui::core::make_value<Derived>();
    skui::core::value_ptr<Base> ptr_copy(ptr);
    skui::core::value_ptr<Base> ptr_copy2(ptr_copy);

    check(dynamic_cast<Derived*>(ptr.get()) != nullptr, "make_value maintains dynamic type");
    check(dynamic_cast<Derived*>(ptr_copy.get()) != nullptr, "copy of make_value maintains dynamic type");
    check(dynamic_cast<Derived*>(ptr_copy2.get()) != nullptr, "copy of of copy of make_value maintains dynamic type");
  }
}

int main()
{
  test_smart_copy();
  test_value_ptr_constructors_get();
  test_value_ptr_copy();
  test_value_ptr_move();
  test_value_ptr_make_value();

  return skui::test::exit_code;
}

