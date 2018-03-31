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

#ifndef SKUI_GUI_LAYOUT_H
#define SKUI_GUI_LAYOUT_H

#include "gui/element.h++"

#include "gui/layout/alignment.h++"
#include "gui/layout/orientation.h++"

#include <memory>
#include <vector>

namespace skui
{
  namespace gui
  {
    class layout : public element
    {
    public:
      ~layout() override;

      void draw(graphics::canvas& canvas,
                const graphics::scalar_position& position) const final;

      graphics::scalar_size implicit_size() const final;

      std::vector<std::unique_ptr<element>> children;

      orientation_flags orientation = orientation::left_to_right;
      alignment child_alignment = alignment::center;

    protected:
      layout(element_ptrs children);

    private:
      virtual std::vector<graphics::scalar_position> calculate_child_offsets() const = 0;
    };
  }
}

#endif
