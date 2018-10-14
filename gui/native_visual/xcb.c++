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

#include "gui/native_visual/xcb.h++"

#include "gui/native_window/xcb.h++"

#include <core/debug.h++>

#include <graphics/swizzle.h++>

#include <xcb/xcb_image.h>

#include <X11/Xlib.h>

namespace skui::gui::native_visual
{
  namespace
  {
    struct xcb_image_deleter
    {
      void operator()(xcb_image_t* image) const { xcb_image_destroy(image); }
    };
    using xcb_image_ptr = std::unique_ptr<xcb_image_t, xcb_image_deleter>;

    xcb_visualtype_t* determine_proper_visualtype(xcb_screen_t* screen)
    {
      for(auto depth_it = xcb_screen_allowed_depths_iterator(screen); depth_it.rem; xcb_depth_next(&depth_it))
      {
        auto depth = depth_it.data;

        if(depth->depth != screen->root_depth)
          continue;

        for(auto visualtype_it = xcb_depth_visuals_iterator(depth); visualtype_it.rem; xcb_visualtype_next(&visualtype_it))
        {
          auto visualtype = visualtype_it.data;
          if(visualtype->bits_per_rgb_value >= 8)
            return visualtype;
        }
      }
      core::debug_print("Could not determine usable XCB visualtype.\n");
      return nullptr;
    }
  }
  xcb::xcb(xcb_connection_t* connection,
           xcb_screen_t* screen)
    : connection{connection}
    , screen{screen}
    , visualtype{determine_proper_visualtype(screen)}
  {}

  xcb_visualid_t xcb::visualid() const
  {
    return visualtype->visual_id;
  }

  xcb::~xcb() = default;

  void xcb::create_surface(std::uintptr_t window)
  {
    this->window = static_cast<xcb_window_t>(window);
    gcontext = xcb_generate_id(connection);
    xcb_create_gc(connection, gcontext, this->window, 0, nullptr);
  }

  void xcb::make_current() const
  {
  }

  void xcb::swap_buffers(const graphics::pixel_size& size) const
  {
    const std::uint16_t width = static_cast<std::uint16_t>(size.width);
    const std::uint16_t height = static_cast<std::uint16_t>(size.height);

    graphics::swizzle(pixel_data);

    xcb_image_ptr image(xcb_image_create(width, height,
                                         XCB_IMAGE_FORMAT_Z_PIXMAP, 32,
                                         24, 32, 32,
                                         XCB_IMAGE_ORDER_LSB_FIRST, XCB_IMAGE_ORDER_LSB_FIRST,
                                         nullptr,
                                         0,
                                         reinterpret_cast<std::uint8_t*>(pixel_data.data())));
    xcb_image_put(connection, window, gcontext, image.get(), 0, 0, 0);
  }
}
