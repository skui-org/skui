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

/*
 * Element
 * Basic GUI building block.
 */

#ifndef SKUI_GUI_ELEMENT_H
#define SKUI_GUI_ELEMENT_H

#include "gui/input.h++"
#include "gui/key.h++"
#include "gui/layout/alignment.h++"
#include "gui/layout/orientation.h++"

#include <core/property.h++>
#include <core/bounded_property.h++>
#include <core/trackable.h++>

#include <graphics/size.h++>

#include <memory>
#include <vector>

namespace skui
{
  namespace graphics
  {
    class canvas;
    class drawable;
  }
  namespace gui
  {
    class element : public core::trackable
    {
    public:
      ~element() override;

      virtual void draw(graphics::canvas& canvas,
                        const graphics::scalar_position& position) = 0;
      void invalidate();

      /// Properties
      // This element by itself
      core::bounded_property<graphics::scalar_size> size;

      // This element inside another
      layout::alignment vertical_alignment = layout::alignment::center;
      layout::alignment horizontal_alignment = layout::alignment::center;

      // This element's children
      layout::orientation_flags orientation = layout::orientation::left_to_right;
      layout::alignment child_alignment = layout::alignment::center;

      bool wrap = false;
      layout::orientation_flags stretch = layout::orientation::horizontal | layout::orientation::vertical;

      // Children
      std::vector<std::unique_ptr<element>> children;

      /// Signals
      // Input
      input::keyboard key;
      input::pointer pointer;

    protected:
      element();

    private:
      bool should_repaint = false;
    };
  }
}

#endif
