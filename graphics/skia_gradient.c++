/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
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

#include "graphics/skia_gradient.h++"

#include "graphics/position.h++"
#include "graphics/skia_utility.h++"

#include <include/effects/SkGradientShader.h>
#include <include/core/SkPaint.h>

namespace skui::graphics
{
  void set_gradient(const color&,
                    SkPaint&,
                    const scalar_position&)
  {}

  void set_gradient(const linear_gradient& linear,
                    SkPaint& paint,
                    const scalar_position& offset)
  {
    auto original_points = linear.points;
    std::for_each(original_points.begin(), original_points.end(),
                  [&offset](auto& point) { point += offset; });

    auto points = convert_to<std::vector<SkPoint>>(linear.points);
    auto colors = convert_to<std::vector<SkColor>>(linear.colors);
    paint.setShader(SkGradientShader::MakeLinear(points.data(),
                                                 colors.data(),
                                                 nullptr,
                                                 static_cast<int>(points.size()),
                                                 SkTileMode::kMirror));
  }

  void set_gradient(const radial_gradient& radial,
                    SkPaint& paint,
                    const scalar_position& offset)
  {
    paint.setShader(SkGradientShader::MakeRadial(convert_to<SkPoint>(radial.center + offset),
                                                 radial.radius,
                                                 convert_to<std::vector<SkColor>>(radial.colors).data(),
                                                 nullptr,
                                                 static_cast<int>(radial.positions.size()),
                                                 SkTileMode::kMirror));
  }

  void set_gradient(const sweep_gradient& sweep,
                    SkPaint& paint,
                    const scalar_position& offset)
  {
    const auto colors = convert_to<std::vector<SkColor>>(sweep.colors);
    paint.setShader(SkGradientShader::MakeSweep(sweep.center.x + offset.x,
                                                sweep.center.y + offset.y,
                                                colors.data(),
                                                nullptr,
                                                static_cast<int>(colors.size())));
  }

  void set_gradient(const two_point_conical_gradient& conical,
                    SkPaint& paint,
                    const scalar_position& offset)
  {
    paint.setShader(SkGradientShader::MakeTwoPointConical(convert_to<SkPoint>(conical.start + offset),
                                                          conical.start_radius,
                                                          convert_to<SkPoint>(conical.end + offset),
                                                          conical.end_radius,
                                                          convert_to<std::vector<SkColor>>(conical.colors).data(),
                                                          nullptr,
                                                          static_cast<int>(conical.colors.size()),
                                                          SkTileMode::kMirror));
  }
}
