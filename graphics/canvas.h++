/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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
 * Graphics canvas on which primitives can be drawn.
 */

#ifndef SKUI_GRAPHICS_CANVAS_H
#define SKUI_GRAPHICS_CANVAS_H

#include "canvas.h++"

#include "shape.h++"

#include <core/bitflag.h++>

namespace skui
{
  namespace graphics
  {
    class rectangle;
    class ellipse;
    class label;
    class path;

    enum class canvas_flag
    {
      none,
      anti_alias
    };
    using canvas_flags = core::bitflag<canvas_flag>;

    class  canvas
    {
    public:
      virtual ~canvas() = default;

      void draw();

      // Primitives
      virtual void draw(const color& background_color) = 0;
      virtual void draw(const rectangle& rectangle,
                        const scalar_position& position) = 0;
      virtual void draw(const ellipse& ellipse,
                        const scalar_position& position) = 0;
      virtual void draw(const label& label,
                        const scalar_position& position) = 0;
      virtual void draw(const path& path,
                        const scalar_position& position) = 0;

    protected:
      canvas(canvas_flags flags);

      canvas_flags flags;
    };
  }
}

#endif
