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

#include "window.h++"

#include <xcb/xcb.h>

namespace skui
{
  namespace gui
  {
    struct xcb_handle
    {
      xcb_connection_t* connection;
      xcb_screen_t* screen;
      xcb_window_t window;
    };

    window::window(pixel_position position, pixel_size initial_size)
      : size{initial_size.width, initial_size.height}
      , maximum_size{}
      , minimum_size{}
      , position{position}
      , icon{}
      , title{}
      , native_handle(new xcb_handle)
    {
      xcb_handle& handle = *static_cast<xcb_handle*>(native_handle);

      // Open the connection to the X Server
      handle.connection = xcb_connect(nullptr, nullptr);

      // Get the first screen
      handle.screen = xcb_setup_roots_iterator(xcb_get_setup(handle.connection)).data;

      // Ask for our window's ID
      handle.window = xcb_generate_id(handle.connection);

      /* Create the window */
      xcb_create_window (handle.connection,
                         XCB_COPY_FROM_PARENT, // depth
                         handle.window,
                         handle.screen->root, // parent window
                         0, 0, // x, y position
                         150, 150, // width, height
                         10, // border_width
                         XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
                         handle.screen->root_visual, // visual
                         0, nullptr); // masks
    }

    window::~window()
    {
      delete static_cast<xcb_handle*>(native_handle);
    }

    void window::show()
    {
      auto& handle = *static_cast<xcb_handle*>(native_handle);

      // Map the window on the screen
      xcb_map_window(handle.connection, handle.window);
      xcb_flush(handle.connection);
    }

    void window::hide()
    {
      auto& handle = *static_cast<xcb_handle*>(native_handle);

      xcb_unmap_window(handle.connection, handle.window);
    }
  }
}
