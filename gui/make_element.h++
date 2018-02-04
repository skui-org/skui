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

/*
 * make_element
 * Convenience function to create element_ptr's.
 */

#ifndef SKUI_GUI_MAKE_ELEMENT_H
#define SKUI_GUI_MAKE_ELEMENT_H

#include "gui/element.h++"

#include <core/utility.h++>

#include <memory>
#include <utility>

namespace skui
{
  namespace gui
  {
    template<typename ElementType, typename... ArgumentTypes>
    std::unique_ptr<ElementType> make(ArgumentTypes&&... arguments)
    {
      return std::make_unique<ElementType>(std::forward<ArgumentTypes>(arguments)...);
    }

    template<typename... ElementTypes>
    element_ptrs make_element_ptrs(std::unique_ptr<ElementTypes>... arguments)
    {
      element_ptrs result;
      result.reserve(sizeof...(ElementTypes));
      skui::core::for_each([&result](element_ptr element_pointer) { result.push_back(std::move(element_pointer)); },
                           std::move(arguments)...);
      return result;
    }
  }
}

#endif
