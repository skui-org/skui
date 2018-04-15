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

#include "column.h++"

#include <cmath>
#include <numeric>

namespace skui
{
  namespace gui
  {
    column::column(element_ptrs children)
      : layout{std::move(children)}
    {
      spacing.value_changed.connect(this, &element::invalidate);
    }

    column::~column() = default;

    graphics::scalar_size column::implicit_size() const
    {
      return std::accumulate(children.begin(), children.end(),
                             graphics::scalar_size{spacing, spacing}*(children.size()-1),
                             [](const auto& value, const auto& child)
                             -> graphics::scalar_size
                             {
                               const auto child_size = child->implicit_size();
                               return {std::max(value.width, child_size.width),
                                       value.height + child_size.height};
                             });
    }

    std::vector<graphics::scalar_position> column::calculate_child_offsets() const
    {
      std::vector<graphics::scalar_position> offsets;
      offsets.reserve(children.size());
      graphics::scalar_position offset{0, 0};

      for(const auto& child : children)
      {
        offsets.emplace_back(offset);

        offset.y += child->implicit_size().height;
      }

      return offsets;
    }
  }
}

