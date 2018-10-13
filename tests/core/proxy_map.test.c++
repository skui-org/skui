/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#include <core/proxy_map.h++>

#include <map>

namespace
{
  using skui::test::check;
  using skui::test::require;

  void test_set_get()
  {
    std::map<int, int> map{{0,1}};
    skui::core::proxy_map<int, int> proxy_map([&map](int key) { return map[key]; },
                                              [&map](int key, int value) { map[key] = value; });

    check(proxy_map[0] == 1, "proxy_map operator[] returns correct value");

    proxy_map.insert(1, 2);
    check(map.find(1) != map.end(), "proxy_map::insert inserts element");
    check(map[1] == 2, "proxy_map::insert inserts correct value");

    auto proxy_value = proxy_map[0];

    map[0] = 2;

    check(proxy_value == 2, "proxy_value calls getter on conversion");

    proxy_value = 3;

    check(map[0] == 3, "proxy_value assignment operator sets proxy value");
  }
}

int main()
{
  test_set_get();

  return skui::test::exit_code;
}
