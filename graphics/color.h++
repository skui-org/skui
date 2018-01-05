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
 * Color, stored as RGBA.
 */

#ifndef SKUI_GRAPHICS_COLOR_H
#define SKUI_GRAPHICS_COLOR_H

#include "color.h++"
#include "pixel.h++"

#include <core/property.h++>
#include <core/trackable.h++>
#include <core/utility.h++>

namespace skui
{
  namespace graphics
  {
    class color
    {
    public:
      explicit constexpr color(std::uint8_t red,
                               std::uint8_t green,
                               std::uint8_t blue,
                               std::uint8_t alpha = 1)
        : alpha{alpha}
        , red{red}
        , green{green}
        , blue{blue}
      {}

      std::uint8_t alpha;
      std::uint8_t red;
      std::uint8_t green;
      std::uint8_t blue;
    };

    namespace colors
    {
      static constexpr color transparent {0, 0, 0, 0};
      static constexpr color white       {255, 255, 255, 255};
      static constexpr color black       {0,   0,   0,   255};
      static constexpr color red         {255, 0,   0,   255};
      static constexpr color green       {0,   255, 0,   255};
      static constexpr color blue        {0,   0,   255, 255};
      static constexpr color grey        {127, 127, 127, 255};
      static constexpr color cyan        {0,   255, 255, 255};
      static constexpr color magenta     {255, 0,   255, 255};
      static constexpr color yellow      {255, 255, 0,   255};
    }
  }
}

#endif
