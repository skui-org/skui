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

/*
 * Skia conversion utilities.
 */

#ifndef SKUI_GRAPHICS_INSIDES
#error "This header contains implementation details and can only be included when building SkUI."
#endif

#ifndef SKUI_GRAPHICS_SKIA_UTILITY_H
#define SKUI_GRAPHICS_SKIA_UTIITYL_H

#include "graphics/color.h++"
#include "graphics/position.h++"

#include <SkColor.h>
#include <SkPoint.h>

#include <algorithm>
#include <iterator>
#include <vector>

namespace skui::graphics
{
  template<typename OutputType, typename InputType>
  OutputType convert_to(const InputType& input);

  template<>
  SkPoint convert_to<SkPoint, scalar_position>(const scalar_position& position);
  template<>
  SkColor convert_to<SkColor, color>(const color& color);

  template<typename OutputContainerType, typename InputContainerType>
  OutputContainerType convert_to(const InputContainerType& input)
  {
    OutputContainerType result;
    result.reserve(input.size());
    std::transform(begin(input), end(input), std::back_inserter(result),
                   convert_to<typename OutputContainerType::value_type,
                   typename InputContainerType::value_type>);
    return result;
  }
}

#endif
