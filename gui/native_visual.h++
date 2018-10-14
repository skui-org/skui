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
 * Abstraction of the graphical backend of a native_window.
 */

#ifndef SKUI_GUI_VISUAL_H
#define SKUI_GUI_VISUAL_H

#include <core/string.h++>

#include <graphics/size.h++>

#include <cstdint>

namespace skui::gui::native_visual
{
  class base
  {
  public:
    base();
    virtual ~base() = 0;

    virtual void create_surface(std::uintptr_t window) = 0;
    virtual void make_current() const = 0;
    virtual void swap_buffers(const graphics::pixel_size& size) const = 0;

    using gl_function_type = void(*)();
    using gl_get_function_type = gl_function_type (*)(void* ctx, const char name[]);
    virtual gl_get_function_type get_gl_function() const;
  };
}

#endif
