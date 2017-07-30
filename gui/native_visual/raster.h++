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
 * Raster Native Visual.
 * Native Visual that provides a local pixel buffer.
 */

#ifndef SKUI_GUI_NATIVE_VISUAL_RASTER_H
#define SKUI_GUI_NATIVE_VISUAL_RASTER_H

#include "gui/native_visual.h++"

#include "gui/native_window.h++"

#include <vector>

namespace skui
{
  namespace gui
  {
    namespace native_visual
    {
      class raster : public base
      {
      public:
        raster();
        ~raster() override;

        std::vector<std::uint32_t>& pixels();
        const std::vector<std::uint32_t>& pixels() const;

      protected:
        mutable std::vector<std::uint32_t> pixel_data;
      };
    }
  }
}

#endif

