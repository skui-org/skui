/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2020 Ruben Van Boxem
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

#include "css/grammar/linear_gradient.h++"

namespace skui::css::grammar
{
  linear_gradient_direction_table::linear_gradient_direction_table()
  {
    add("left", css::left)
       ("right", css::right)
       ("top", css::top)
       ("bottom", css::bottom)
       ("left top", css::top_left)
       ("left bottom", css::bottom_left)
       ("right top", css::top_right)
       ("right bottom", css::bottom_right)
       ("top left", css::top_left)
       ("top right", css::top_right)
       ("bottom left", css::bottom_left)
       ("bottom right", css::bottom_right)
       ;
  }
}
