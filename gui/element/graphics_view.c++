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

#include "gui/element/graphics_view.h++"

#include <graphics/canvas.h++>
#include <graphics/drawable.h++>

namespace skui::gui
{
  graphics_view::graphics_view(const graphics::scene& scene)
    : scene{scene}
  {}

  graphics_view::~graphics_view() = default;

  void graphics_view::draw(graphics::canvas& canvas,
                           const graphics::scalar_position& position) const
  {
    canvas.draw(scene.background_color, {{position, size}});

    for(const auto& [offset, drawable] : scene.drawables)
    {
      const auto top_left = position+offset;
      drawable->draw(canvas, top_left, {{top_left, size}});
    }
  }

  graphics::scalar_size graphics_view::implicit_size(const graphics::canvas&) const
  {
    return size;
  }
}
