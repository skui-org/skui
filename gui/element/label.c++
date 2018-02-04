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

#include "gui/element/label.h++"

#include <graphics/color.h++>
#include <graphics/shape/text.h++>

#include <graphics/canvas.h++>
#include "graphics/shape/ellipse.h++"
#include "graphics/shape/rectangle.h++"
#include "graphics/gradient/sweep_gradient.h++"

namespace skui
{
  namespace gui
  {
    label::label(core::string text)
      : graphics_label(text)
    {
      graphics_label.fill.color = graphics::colors::white;
      graphics_label.font_size = 20;

      this->text.value_changed.connect([this](const core::string& text) { graphics_label.characters = text; });
      this->text.value_changed.connect(this, &label::invalidate);
    }

    label::~label() = default;

    void label::draw(graphics::canvas& canvas,
                     const graphics::scalar_position& position) const
    {
      graphics_label.draw(canvas, position);
    }

    graphics::scalar_size label::implicit_size() const
    {
      return graphics_label.implicit_size();
    }
  }
}
