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
 * Primitive shape base class.
 */

#ifndef SKUI_GRAPHICS_SHAPE_H
#define SKUI_GRAPHICS_SHAPE_H

#include "color.h++"
#include "drawable.h++"
#include "gradient.h++"
#include "pixel.h++"
#include "scalar.h++"

#include <core/utility.h++>

namespace skui
{
  namespace graphics
  {
    class shape : public drawable
    {
    public:
      shape();
      ~shape() override;

      struct
      {
        graphics::color color = colors::white;
        std::unique_ptr<graphics::gradient> gradient;
      } fill;

      struct
      {
        scalar thickness = 0;
        scalar radius = 0;
        graphics::color color = graphics::colors::transparent;
      } border;
    };
  }
}

#endif
