/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ruben Van Boxem
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
 * Window abstraction.
 */

#ifndef SKUI_GUI_WINDOW_H
#define SKUI_GUI_WINDOW_H

#include "icon.h++"
#include "position.h++"
#include "size.h++"

#include <core/string.h++>

namespace skui
{
  namespace gui
  {
    class window
    {
    public:
      window(pixel_position position = {0, 0}, pixel_size initial_size = {800, 600});

      pixel_size size;
      pixel_size maximum_size;
      pixel_size minimum_size;

      pixel_position position;

      core::property<gui::icon> icon;
      core::property<core::string> title;

      void show();
      void hide();

    private:
      void* native_handle;
    };
  }
}

#endif
