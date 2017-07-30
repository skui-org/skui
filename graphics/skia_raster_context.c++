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

#include "graphics/skia_raster_context.h++"

#include "graphics/skia_raster_canvas.h++"

#include <core/debug.h++>

#include <thread>

namespace skui
{
  namespace graphics
  {
    skui::graphics::skia_raster_context::skia_raster_context(std::vector<std::uint32_t>& pixels)
      : context()
      , pixels(pixels)
    {}

    std::unique_ptr<canvas> skia_raster_context::create_canvas(const pixel_size& size,
                                                               canvas_flags flags) const
    {
      pixels.resize(size.width*size.height);

      return std::make_unique<skia_raster_canvas>(pixels, size, flags);
    }
  }
}
