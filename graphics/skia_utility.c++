/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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

#include "graphics/skia_utility.h++"

namespace skui
{
    namespace graphics
    {
      SkPoint to_skia(const scalar_position& position)
      {
        return SkPoint::Make(position.x, position.y);
      }

      std::vector<SkPoint> to_skia(const std::vector<scalar_position>& positions)
      {
        std::vector<SkPoint> points;
        points.reserve(positions.size());
        std::transform(positions.begin(), positions.end(), std::back_inserter(points),
                       [](const scalar_position& position) { return to_skia(position); });
        return points;
      }

      SkColor to_skia(const color& color)
      {
        return SkColorSetARGB(color.alpha, color.red, color.green, color.blue);
      }

      std::vector<SkColor> to_skia(const std::vector<color>& colors)
      {
        std::vector<SkColor> skia_colors;
        skia_colors.reserve(colors.size());
        std::transform(colors.begin(), colors.end(), std::back_inserter(skia_colors),
                       [](const color& color) { return to_skia(color); });
        return skia_colors;
      }
  }
}
