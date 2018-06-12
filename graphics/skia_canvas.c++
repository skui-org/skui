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

#include "graphics/skia_canvas.h++"

#include <core/debug.h++>

#include "graphics/gradient/linear_gradient.h++"
#include "graphics/gradient/radial_gradient.h++"
#include "graphics/gradient/sweep_gradient.h++"
#include "graphics/gradient/two_point_conical_gradient.h++"

#include "graphics/shape/ellipse.h++"
#include "graphics/shape/text.h++"
#include "graphics/shape/path.h++"
#include "graphics/shape/rectangle.h++"

#include "graphics/skia_gradient.h++"
#include "graphics/skia_utility.h++"

#include <SkCanvas.h>
#include <SkColor.h>
#include <SkPath.h>
#include <SkRRect.h>
#include <SkSurface.h>

#include <array>

namespace skui
{
  namespace graphics
  {
    namespace
    {
      SkPaint make_border_paint(const shape& shape,
                                const canvas_flags& flags)
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

      SkPaint make_fill_paint(const shape& shape,
                              const scalar_position& offset,
                              const canvas_flags& flags)
      {
        SkPaint paint;

        paint.setStyle(SkPaint::Style::kFill_Style);

        if(std::holds_alternative<color>(shape.fill))
        {
          const auto& color = std::get<graphics::color>(shape.fill);
          paint.setARGB(color.alpha,
                        color.red,
                        color.green,
                        color.blue);
        }
        else
        {
          const auto& gradient = std::get<graphics::gradient>(shape.fill);
          std::visit([&paint, &offset](auto&& specific_gradient)
                     { set_gradient(specific_gradient, paint, offset); },
                     gradient);
        }

        if(flags.test(canvas_flag::anti_alias))
          paint.setAntiAlias(true);

        return paint;
      }

      std::array<SkPaint, 2> make_paint(const shape& shape,
                                        const scalar_position& offset,
                                        const canvas_flags& flags)
      {
        return {{make_fill_paint(shape, offset, flags),
                 make_border_paint(shape, flags)}};
      }

      struct canvas_guard
      {
        canvas_guard(SkCanvas* canvas,
                     const std::optional<scalar_bounding_box>& clipping_box)
          : auto_restore(canvas, true)
        {
          if(clipping_box)
          {
            canvas->clipRect(SkRect::MakeXYWH(clipping_box->top_left.x,
                                              clipping_box->top_left.y,
                                              clipping_box->size.width,
                                              clipping_box->size.height));
          }
        }
        SkAutoCanvasRestore auto_restore;
      };
    }

    skia_canvas::skia_canvas(canvas_flags flags)
      : canvas{flags}
      , surface{nullptr}
    {}

    void skia_canvas::draw(const color& background_color,
                           const std::optional<scalar_bounding_box>& clipping_box)
    {
      auto canvas = surface->getCanvas();

      const canvas_guard guard(canvas, clipping_box);

      canvas->drawColor(convert_to<SkColor>(background_color));
    }

    void skia_canvas::draw(const rectangle& rectangle,
                           const scalar_position& position,
                           const std::optional<scalar_bounding_box>& clipping_box)
    {
      auto canvas = surface->getCanvas();

      const auto rect = SkRect::MakeXYWH(position.x, position.y,
                                         rectangle.size.width,rectangle.size.height);
      const auto rounded_rect = SkRRect::MakeRectXY(rect,
                                                    rectangle.border.radius,
                                                    rectangle.border.radius);
      SkPath border;
      border.addRoundRect(rect, rectangle.border.radius, rectangle.border.radius);

      for(const auto& paint : make_paint(rectangle, position, flags))
      {
          canvas->drawRRect(rounded_rect, paint);
      }
    }

    void skia_canvas::draw(const ellipse& ellipse,
                           const scalar_position& position,
                           const std::optional<scalar_bounding_box>& clipping_box)
    {
      auto canvas = surface->getCanvas();

      const canvas_guard guard(canvas, clipping_box);

      for(const auto& paint : make_paint(ellipse, position, flags))
      {
          canvas->drawOval(SkRect::MakeXYWH(position.x, position.y,
                                            ellipse.axes.height, ellipse.axes.width),
                           paint);
      }
    }

    void skia_canvas::draw(const text& text,
                           const scalar_position& position,
                           const std::optional<scalar_bounding_box>& clipping_box)
    {
      auto canvas = surface->getCanvas();

      for(auto& paint : make_paint(text, position, flags))
      {
        paint.setTextSize(text.font_size);
        canvas->drawText(text.characters.c_str(), text.characters.size(),
                         position.x, position.y+text.font_size,
                         paint);
      }
    }

    void skia_canvas::draw(const path& path,
                           const scalar_position& position,
                           const std::optional<scalar_bounding_box>& clipping_box)
    {
      auto canvas = surface->getCanvas();

      const canvas_guard guard(canvas, clipping_box);

      SkPath skia_path;

      for(const auto& paint : make_paint(path, position, flags))
      {
          canvas->drawPath(skia_path,
                           paint);
      }
    }
  }
}
