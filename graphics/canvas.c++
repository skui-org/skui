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

#include "graphics/canvas.h++"

#include "graphics/gradient/linear_gradient.h++"
#include "graphics/gradient/sweep_gradient.h++"

#include "graphics/shape/ellipse.h++"
#include "graphics/shape/text.h++"
#include "graphics/shape/rectangle.h++"

namespace skui
{
  namespace graphics
  {
    void canvas::draw()
    {
      rectangle square({140, 140});
      square.fill.color = colors::red;
      square.border.thickness = 20; // black by default

      rectangle marker({140,140});
      marker.fill.color = colors::transparent;
      marker.border.thickness = 1;
      marker.border.color = colors::green;

      ellipse circle({140, 140});
      const scalar_position center{220,220};
      const std::vector<color> rainbow{colors::cyan,
                                       colors::magenta,
                                       colors::yellow,
                                       colors::cyan};
      circle.fill.gradient = std::make_unique<sweep_gradient>(center, rainbow);

      text text_label("Hello Skui!");
      text_label.fill.color = colors::white;

      draw(colors::black);
      draw(square, {10, 10});
      draw(marker, {10.5,10.5});
      draw(circle, {150, 150});
      draw(text_label, {300, 300});
    }

    canvas::canvas(canvas_flags flags)
      : flags(flags)
    {

    }
  }
}
