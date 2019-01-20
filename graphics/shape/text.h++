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
 * A text shape.
 */

#ifndef SKUI_GRAPHICS_TEXT_H
#define SKUI_GRAPHICS_TEXT_H

#include "graphics/shape.h++"
#include "graphics/style/font.h++"

#include <core/string.h++>

namespace skui::graphics
{
  class text : public shape
  {
  public:
    text(core::string text,
         style::font font = {});
    ~text() override;

    void draw(canvas& canvas,
              const scalar_position& position,
              const std::optional<scalar_bounding_box>& clipping_box = {}) const override;

    scalar_size implicit_size(const canvas& canvas) const override;

    core::string characters;
    style::font font;
    style::border& outline = shape::border;
  };
}

#endif
