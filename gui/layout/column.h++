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

#ifndef SKUI_GUI_LAYOUT_COLUMN_H
#define SKUI_GUI_LAYOUT_COLUMN_H

#include "gui/layout.h++"
#include "gui/make_element.h++"

namespace skui::gui
{
  class column : public layout
  {
  public:
    template<typename... ElementPointerTypes>
    column(ElementPointerTypes&&... element_pointers)
      : column{make_element_ptrs(std::forward<ElementPointerTypes>(element_pointers)...)}
    {}
    column(element_ptrs elements);
    ~column() override;

    graphics::scalar_size implicit_size(const graphics::canvas& canvas) const override;

  private:
    std::vector<graphics::scalar_position> calculate_child_offsets(const graphics::canvas& canvas) const override;
  };

  using column_ptr = std::unique_ptr<column>;
}

#endif
