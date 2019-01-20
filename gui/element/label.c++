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

#include "gui/element/label.h++"

#include <graphics/color.h++>
#include <graphics/shape/text.h++>

#include <graphics/canvas.h++>
#include "graphics/shape/ellipse.h++"
#include "graphics/shape/rectangle.h++"
#include "graphics/gradient/sweep_gradient.h++"

namespace skui::gui
{
  namespace
  {
    graphics::text make_text(const core::string& text,
                             const graphics::style::fill& fill,
                             const graphics::style::border& outline,
                             const graphics::style::font& font)
    {
      graphics::text result(text);
      result.fill = fill;
      result.border = outline;
      result.font = font;
      return result;
    }
  }

  label::label(core::string text)
    : text{text}
    , fill{}
  {}

  label::~label() = default;

  void label::draw(graphics::canvas& canvas,
                   const graphics::scalar_position& position) const
  {
    auto graphics_text = make_text(text, fill, outline, font);
    graphics::rectangle rectangle{canvas.measure_text(graphics_text)};
    rectangle.border = border;
    rectangle.fill = background;
    element::draw(canvas,
    {&rectangle, &graphics_text},
    {position, position + graphics::scalar_position{border.thickness, border.thickness}});
  }

  graphics::scalar_size label::implicit_size(const graphics::canvas& canvas) const
  {
    auto graphics_text = make_text(text, fill, outline, font);
    const auto text_size = canvas.measure_text(graphics_text);
    return text_size + 2.f*graphics::scalar_size{border.thickness, border.thickness};
  }
}
