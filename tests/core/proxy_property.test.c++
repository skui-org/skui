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

#include "property_tests.h++"

#include "core/proxy_property.h++"

namespace
{
  using skui::test::check;

  int value;
  int getter() { return value; }
  void setter(int new_value) { value = new_value; }

  struct mock_proxy_property : public skui::core::proxy_property<int>
  {
    mock_proxy_property(int initial_value = 0)
      : proxy_property(initial_value, &setter, &getter)
    {}

    using proxy_property::operator=;
  };

  void test_proxy_value_modified()
  {
    bool slot_called = false;
    skui::core::proxy_property<int> property(&setter, &getter);
    property.value_changed.connect([&slot_called](int) { slot_called = true; });

    value = 0;
    property = 1;

    check(value == 1, "proxied object changed through proxy_property.");
  }
}

int main()
{
  skui::test::run_all_property_tests<mock_proxy_property>();

  test_proxy_value_modified();

  return skui::test::exit_code;
}
