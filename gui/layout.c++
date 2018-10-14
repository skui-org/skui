/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#include "layout.h++"

#include <algorithm>
#include <utility>

namespace skui::gui
{
  layout::~layout() = default;

  layout::layout(element_ptrs children)
    : children{std::move(children)}
    , spacing{0}
  {
    spacing.value_changed.connect(this, &element::invalidate);
  }

  void layout::draw(graphics::canvas& canvas, const graphics::scalar_position& position) const
  {
    auto child_offsets = calculate_child_offsets(canvas);
    const auto padded_position = position + graphics::scalar_position{padding.left, padding.right};
    std::for_each(child_offsets.begin(), child_offsets.end(),
                  [&padded_position](auto& offset) { offset += padded_position; });

    for(std::size_t i = 0; i < children.size(); ++i)
    {
      children[i]->draw(canvas, child_offsets[i]);
    }
  }
}
