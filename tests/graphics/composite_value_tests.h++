/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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

#ifndef SKUI_TEST_COMPOSITE_VALUE_TESTS_H
#define SKUI_TEST_COMPOSITE_VALUE_TESTS_H

#include <core/utility/bound.h++>

namespace skui
{
  namespace test
  {
    template<typename CompositeValueType>
    void test_equality_operators()
    {
      constexpr CompositeValueType size{1,2};

      static_assert(  size == CompositeValueType{1,2},  "operator== returns true for same size");
      static_assert(!(size == CompositeValueType{2,2}), "operator== returns false for different width");
      static_assert(!(size == CompositeValueType{1,1}), "operator== returns false for different height");
      static_assert(!(size == CompositeValueType{2,1}), "operator== returns false for different size");

      static_assert(!(size != CompositeValueType{1,2}), "operator!= returns false for same size");
      static_assert(  size != CompositeValueType{2,2},  "operator!= returns true for different width");
      static_assert(  size != CompositeValueType{1,1},  "operator!= returns true for different height");
      static_assert(  size != CompositeValueType{2,1},  "operator!= returns true for different size");
    }

    template<typename CompositeValueType>
    void test_numeric_limits()
    {
      static_assert(std::numeric_limits<CompositeValueType>::min() == CompositeValueType{std::numeric_limits<typename CompositeValueType::value_type>::min(),
                                                                                 std::numeric_limits<typename CompositeValueType::value_type>::min()},
            "numeric_limits::min returns correct value");

      static_assert(std::numeric_limits<CompositeValueType>::lowest() == CompositeValueType{std::numeric_limits<typename CompositeValueType::value_type>::lowest(),
                                                                                    std::numeric_limits<typename CompositeValueType::value_type>::lowest()},
            "numeric_limits::lowest returns correct value");

      static_assert(std::numeric_limits<CompositeValueType>::max() == CompositeValueType{std::numeric_limits<typename CompositeValueType::value_type>::max(),
                                                                                 std::numeric_limits<typename CompositeValueType::value_type>::max()},
            "numeric_limits::max returns correct value");
    }

    template<typename CompositeValueType>
    void test_bound()
    {
      constexpr skui::core::bound<CompositeValueType> bound;

      static_assert(bound({-1, -1}, {0, 0}, {2, 2}) == CompositeValueType{0, 0});
      static_assert(bound({-1,  0}, {0, 0}, {2, 2}) == CompositeValueType{0, 0});
      static_assert(bound({-1,  1}, {0, 0}, {2, 2}) == CompositeValueType{0, 1});
      static_assert(bound({-1,  2}, {0, 0}, {2, 2}) == CompositeValueType{0, 2});
      static_assert(bound({-1,  3}, {0, 0}, {2, 2}) == CompositeValueType{0, 2});
      static_assert(bound({ 0, -1}, {0, 0}, {2, 2}) == CompositeValueType{0, 0});
      static_assert(bound({ 0,  0}, {0, 0}, {2, 2}) == CompositeValueType{0, 0});
      static_assert(bound({ 0,  1}, {0, 0}, {2, 2}) == CompositeValueType{0, 1});
      static_assert(bound({ 0,  2}, {0, 0}, {2, 2}) == CompositeValueType{0, 2});
      static_assert(bound({ 0,  3}, {0, 0}, {2, 2}) == CompositeValueType{0, 2});
      static_assert(bound({ 1, -1}, {0, 0}, {2, 2}) == CompositeValueType{1, 0});
      static_assert(bound({ 1,  0}, {0, 0}, {2, 2}) == CompositeValueType{1, 0});
      static_assert(bound({ 1,  1}, {0, 0}, {2, 2}) == CompositeValueType{1, 1});
      static_assert(bound({ 1,  2}, {0, 0}, {2, 2}) == CompositeValueType{1, 2});
      static_assert(bound({ 1,  3}, {0, 0}, {2, 2}) == CompositeValueType{1, 2});
      static_assert(bound({ 2, -1}, {0, 0}, {2, 2}) == CompositeValueType{2, 0});
      static_assert(bound({ 2,  0}, {0, 0}, {2, 2}) == CompositeValueType{2, 0});
      static_assert(bound({ 2,  1}, {0, 0}, {2, 2}) == CompositeValueType{2, 1});
      static_assert(bound({ 2,  2}, {0, 0}, {2, 2}) == CompositeValueType{2, 2});
      static_assert(bound({ 2,  3}, {0, 0}, {2, 2}) == CompositeValueType{2, 2});
      static_assert(bound({ 3, -1}, {0, 0}, {2, 2}) == CompositeValueType{2, 0});
      static_assert(bound({ 3,  0}, {0, 0}, {2, 2}) == CompositeValueType{2, 0});
      static_assert(bound({ 3,  1}, {0, 0}, {2, 2}) == CompositeValueType{2, 1});
      static_assert(bound({ 3,  2}, {0, 0}, {2, 2}) == CompositeValueType{2, 2});
      static_assert(bound({ 3,  3}, {0, 0}, {2, 2}) == CompositeValueType{2, 2});


    }

    template<typename CompositeValueType>
    void run_all_composite_value_tests()
    {
      test_equality_operators<CompositeValueType>();
      test_numeric_limits<CompositeValueType>();
      test_bound<CompositeValueType>();
    }
  }
}

#endif
