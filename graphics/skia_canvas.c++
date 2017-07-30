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

#include "graphics/skia_canvas.h++"

#include <core/debug.h++>

#include "graphics/gradient/linear_gradient.h++"
#include "graphics/gradient/radial_gradient.h++"
#include "graphics/gradient/sweep_gradient.h++"
#include "graphics/gradient/two_point_conical_gradient.h++"

#include "graphics/shape/ellipse.h++"
#include "graphics/shape/label.h++"
#include "graphics/shape/path.h++"
#include "graphics/shape/rectangle.h++"

#include "graphics/skia_utility.h++"

#include <SkCanvas.h>
#include <SkColor.h>
#include <SkGradientShader.h>
#include <SkPath.h>
#include <SkRRect.h>

namespace skui
{
  namespace graphics
  {
    skia_canvas::skia_canvas(//sk_sp<SkSurface> surface,
                             float pixel_offset,
                             canvas_flags flags)
      : canvas(flags)
      , surface(nullptr/*surface*/)
      , pixel_offset(pixel_offset)
    {
      //SkASSERT(surface);
    }

    void skia_canvas::draw(const color& background_color)
    {
      auto canvas = surface->getCanvas();

      canvas->drawColor(to_skia(background_color));
    }

    void skia_canvas::draw(const rectangle& rectangle)
    {
      auto canvas = surface->getCanvas();

      const auto rect = SkRect::MakeXYWH(rectangle.position.x,
                                         rectangle.position.y,
                                         rectangle.size.width,
                                         rectangle.size.height);
      const auto rounded_rect = SkRRect::MakeRectXY(rect,
                                                    rectangle.border.radius,
                                                    rectangle.border.radius);
      SkPath border;
      border.addRoundRect(rect, rectangle.border.radius, rectangle.border.radius);

      canvas->save();
      canvas->translate(pixel_offset, pixel_offset);
      for(const auto& paint : {make_fill_paint(rectangle), make_border_paint(rectangle)})
      {
          canvas->drawRRect(rounded_rect, paint);
      }
      canvas->restore();
    }

    void skia_canvas::draw(const ellipse& ellipse)
    {
      auto canvas = surface->getCanvas();

      canvas->save();
      canvas->translate(pixel_offset, pixel_offset);
      for(const auto& paint : make_paint(ellipse))
      {
          canvas->drawOval(SkRect::MakeXYWH(ellipse.position.x, ellipse.position.y,
                                            ellipse.axes.height, ellipse.axes.width),
                           paint);
      }
      canvas->restore();
    }

    void skia_canvas::draw(const label& label)
    {
      auto canvas = surface->getCanvas();;

      canvas->save();
      canvas->translate(pixel_offset, pixel_offset);
      for(const auto& paint : make_paint(label))
      {
          canvas->drawText(label.text.c_str(), label.text.size(),
                           label.position.x, label.position.y,
                           paint);
      }
      canvas->restore();
    }

    void skia_canvas::draw(const path& path)
    {
      auto canvas = surface->getCanvas();

      SkPath skia_path;

      for(const auto& paint : make_paint(path))
      {
          canvas->drawPath(skia_path,
                           paint);
      }
    }

    std::vector<SkPaint> skia_canvas::make_paint(const shape& shape) const
    {
      return {make_fill_paint(shape), make_border_paint(shape)};
    }

    SkPaint skia_canvas::make_border_paint(const shape& shape) const
    {
      SkPaint paint;

      paint.setStyle(SkPaint::Style::kStroke_Style);

      paint.setARGB(shape.border.color.alpha,
                    shape.border.color.red,
                    shape.border.color.green,
                    shape.border.color.blue);

      paint.setStrokeWidth(shape.border.thickness);

      if(flags.test(canvas_flag::anti_alias))
          paint.setAntiAlias(true);

      return paint;
    }

    SkPaint skia_canvas::make_fill_paint(const shape& shape) const
    {
      SkPaint paint;

      paint.setStyle(SkPaint::Style::kFill_Style);

      paint.setARGB(shape.fill.color.alpha,
                    shape.fill.color.red,
                    shape.fill.color.green,
                    shape.fill.color.blue);

      if(shape.fill.gradient)
      {
          set_gradient(paint, *shape.fill.gradient);
      }

      if(flags.test(canvas_flag::anti_alias))
        paint.setAntiAlias(true);

      return paint;
    }

    void skia_canvas::set_gradient(SkPaint& paint, const gradient& gradient) const
    {
      switch(gradient.type)
      {
          case gradient_type::linear:
          {
              const auto& linear = static_cast<const linear_gradient&>(gradient);
              auto points = to_skia(linear.points);
              auto colors = to_skia(linear.colors);
              paint.setShader(SkGradientShader::MakeLinear(points.data(),
                                                           colors.data(),
                                                           nullptr,
                                                           static_cast<int>(points.size()),
                                                           SkShader::TileMode::kMirror_TileMode));
              return;
          }
          case gradient_type::radial:
          {
              const auto& radial = static_cast<const radial_gradient&>(gradient);
              paint.setShader(SkGradientShader::MakeRadial(to_skia(radial.center),
                                                           radial.radius,
                                                           to_skia(radial.colors).data(),
                                                           nullptr,
                                                           static_cast<int>(radial.positions.size()),
                                                           SkShader::TileMode::kMirror_TileMode));
              return;
          }
          case gradient_type::two_point_conical:
          {
              const auto& conical = static_cast<const two_point_conical_gradient&>(gradient);
              paint.setShader(SkGradientShader::MakeTwoPointConical(to_skia(conical.start),
                                                                    conical.start_radius,
                                                                    to_skia(conical.end),
                                                                    conical.end_radius,
                                                                    to_skia(conical.colors).data(),
                                                                    nullptr,
                                                                    static_cast<int>(conical.colors.size()),
                                                                    SkShader::TileMode::kMirror_TileMode));
              return;
          }
          case gradient_type::sweep:
          {
              const auto& sweep = static_cast<const sweep_gradient&>(gradient);
              const auto colors = to_skia(sweep.colors);
              paint.setShader(SkGradientShader::MakeSweep(sweep.center.x,
                                                          sweep.center.y,
                                                          colors.data(),
                                                          nullptr,
                                                          static_cast<int>(colors.size())));
              return;
          }
      }
    }
  }
}
