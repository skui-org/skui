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

#include "gui/element.h++"

#include <graphics/drawable.h++>

namespace skui::gui
{
  bool element::show_invisible = false;

  element::~element() = default;

  void element::invalidate()
  {
    should_repaint = true;
  }

  void element::draw(graphics::canvas& canvas,
                     const std::vector<const graphics::drawable*>& drawables,
                     const std::vector<graphics::scalar_position>& positions,
                     const std::optional<graphics::scalar_bounding_box>& clipping_box) const
  {
    for(std::size_t i = 0; i < drawables.size(); ++i)
    {
      drawables[i]->draw(canvas,
                         positions[i] + graphics::scalar_position{padding.left, padding.top},
                         clipping_box);
    }
  }

  element::element() = default;
}
