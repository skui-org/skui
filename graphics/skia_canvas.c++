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

#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <include/core/SkFont.h>
#include <include/core/SkFontMetrics.h>
#include <include/core/SkPath.h>
#include <include/core/SkRRect.h>
#include <include/core/SkSurface.h>

#include <array>

namespace skui::graphics
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

      paint.setAntiAlias(flags.test(canvas_flag::anti_alias));

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

      paint.setAntiAlias(flags.test(canvas_flag::anti_alias));

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
        : auto_restore(canvas, clipping_box.has_value())
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

  void skia_canvas::draw(const style::fill& background,
                         const std::optional<scalar_bounding_box>& clipping_box)
  {
    auto canvas = surface->getCanvas();

    const canvas_guard guard(canvas, clipping_box);

    if(std::holds_alternative<color>(background))
      canvas->drawColor(convert_to<SkColor>(std::get<color>(background)));
    //TODO handle gradient background
  }

  void skia_canvas::draw(const rectangle& rectangle,
                         const scalar_position& position,
                         const std::optional<scalar_bounding_box>& clipping_box)
  {
    auto canvas = surface->getCanvas();

    const canvas_guard guard(canvas, clipping_box);

    const auto& [fill_paint, border_paint] = make_paint(rectangle, position, flags);

    const auto& border = rectangle.border;

    const auto fill_radius = std::max(0.f, border.radius-border.thickness);
    const auto fill_rect = SkRRect::MakeRectXY(SkRect::MakeXYWH(position.x+border.thickness,
                                                                position.y+border.thickness,
                                                                rectangle.size.width,
                                                                rectangle.size.height),
                                               fill_radius,
                                               fill_radius);
    // The border is drawn by stroking, which fills half of the stroke thickness on both sides.
    const auto border_rect = SkRRect::MakeRectXY(SkRect::MakeXYWH(position.x+.5f*border.thickness,
                                                                  position.y+.5f*border.thickness,
                                                                  rectangle.size.width+border.thickness,
                                                                  rectangle.size.height+border.thickness),
                                                 rectangle.border.radius,
                                                 rectangle.border.radius);

    // Another possibility here is to use drawDRRect to draw the border pixel-perfectly
    // Unfortunately, this precludes any possibility of dashed lines etc.
    canvas->drawRRect(fill_rect, fill_paint);
    canvas->drawRRect(border_rect, border_paint);
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
                                        ellipse.axes.width, ellipse.axes.height),
                       paint);
    }
  }

  void skia_canvas::draw(const text& text,
                         const scalar_position& position,
                         const std::optional<scalar_bounding_box>& clipping_box)
  {
    auto canvas = surface->getCanvas();

    const canvas_guard guard(canvas, clipping_box);

    auto [fill_paint, border_paint] = make_paint(text, position, flags);
    SkFont font;
    font.setSize(text.font.size);

    SkFontMetrics metrics;
    font.getMetrics(&metrics);

    SkScalar offset = -metrics.fAscent;
    // 0.5f offset is to correct an apparent offset in the size/positioning of text
    canvas->drawSimpleText(text.characters.c_str(),
                           text.characters.size(),
                           SkTextEncoding::kUTF8,
                           position.x - .5f,
                           position.y + offset - .5f,
                           font,
                           fill_paint);

    canvas->drawSimpleText(text.characters.c_str(),
                           text.characters.size(),
                           SkTextEncoding::kUTF8,
                           position.x - .5f,
                           position.y + offset - .5f,
                           font,
                           border_paint);
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

  scalar_size skia_canvas::measure_text(const text& text) const
  {
    SkPaint paint = text.border.color == colors::transparent ? make_fill_paint(text, {0, 0}, flags)
                                                             : make_border_paint(text, flags);
    SkFont font;
    font.setSize(text.font.size);

    SkFontMetrics metrics;
    font.getMetrics(&metrics);

    SkRect bounds;
    const SkScalar width = font.measureText(text.characters.c_str(),
                                            text.characters.size(),
                                            SkTextEncoding::kUTF8,
                                            &bounds,
                                            &paint);
    const SkScalar height = std::abs(metrics.fAscent - metrics.fDescent);

    core::debug_print("printing text: \'", text.characters, "\'\n",
                      "bounding rect top: (", bounds.left(), ", ", bounds.top(), ")\n",
                      "bounding rect size: ", bounds.width(), "x", bounds.height(), "\n",
                      "font height: ", height, "\n",
                      "text width: ", width, "\n");

    return {width, height};
  }
}
