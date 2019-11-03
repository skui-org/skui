/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

#include "gui/native_window/xcb.h++"

#include "gui/native_visual/xcb.h++"

#include <core/debug.h++>

#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>

namespace
{
  xcb_screen_t* screen_of_display(xcb_connection_t* connection,
                                  int screen)
  {
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(connection));
    do
    {
      if(screen == 0)
        return iter.data;

      --screen;
      xcb_screen_next(&iter);
    } while(iter.rem != 0);

    return nullptr;
  }

  // For some reason, if this code is called from a member function, events don't come through correctly.
  void make_xcb_window(const skui::graphics::pixel_position& position,
                       const skui::graphics::pixel_size& size,
                       xcb_connection_t* connection,
                       xcb_screen_t* preferred_screen,
                       xcb_visualid_t visualid,
                       xcb_window_t& window)
  {
    window = xcb_generate_id(connection);

    static const uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    static const uint32_t values[] = { preferred_screen->white_pixel,
                                       XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_STRUCTURE_NOTIFY |
                                       XCB_EVENT_MASK_BUTTON_PRESS   | XCB_EVENT_MASK_BUTTON_RELEASE |
                                       XCB_EVENT_MASK_POINTER_MOTION |
                                       XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW |
                                       XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE };

    xcb_create_window(connection,
                      XCB_COPY_FROM_PARENT,
                      window,
                      preferred_screen->root,
                      static_cast<std::int16_t>(position.x), static_cast<std::int16_t>(position.y),
                      static_cast<std::uint16_t>(size.width), static_cast<std::uint16_t>(size.height),
                      10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      visualid,
                      mask, values);
  }
}

namespace skui::gui::native_window
{
  xcb_data::xcb_data()
    : preferred_screen_index{}
    , connection{xcb_connect(nullptr, &preferred_screen_index)}
    , preferred_screen{screen_of_display(connection, preferred_screen_index)}
  {}

  xcb_data::xcb_data(xcb_connection_t* connection)
    : preferred_screen_index{}
    , connection{connection}
    , preferred_screen{screen_of_display(connection, preferred_screen_index)}
  {}

  xcb_data::~xcb_data() = default;

  xcb::xcb()
    : xcb_data{}
    , base{std::make_unique<native_visual::xcb>(connection, preferred_screen)}
  {}

  xcb::~xcb() = default;

  void xcb::show()
  {
    xcb_map_window(connection, static_cast<xcb_window_t>(window));
    xcb_flush(connection);
  }

  void xcb::hide()
  {
    xcb_unmap_window(connection, static_cast<xcb_window_t>(window));
    xcb_flush(connection);
  }

  void xcb::close()
  {
    core::debug_print("Closing XCB window\n");
    xcb_unmap_window(connection, window);
    xcb_destroy_window(connection, window);
    xcb_flush(connection);
  }

  core::string xcb::get_title() const
  {
    xcb_get_property_cookie_t cookie = xcb_get_property(connection,
                                                        0,
                                                        window,
                                                        XCB_ATOM_WM_NAME,
                                                        XCB_ATOM_STRING,
                                                        0,
                                                        0);

    core::unique_free_ptr<xcb_get_property_reply_t> reply(
          xcb_get_property_reply(connection,
                                 cookie,
                                 nullptr));

    if(reply)
    {
      int length = xcb_get_property_value_length(reply.get());
      if(length > 0)
      {
        const char* result = static_cast<char*>(xcb_get_property_value(reply.get()));
        return core::string(result, result + length);
      }
    }
    return "";
  }

  void xcb::set_title(const core::string& title)
  {
    xcb_change_property(connection,
                        XCB_PROP_MODE_REPLACE,
                        window,
                        XCB_ATOM_WM_NAME,
                        XCB_ATOM_STRING,
                        8,
                        static_cast<std::uint32_t>(title.size()),
                        title.c_str());
    xcb_flush(connection);
  }

  std::pair<graphics::pixel_position, graphics::pixel_size> xcb::get_current_geometry() const
  {
    // fetch true dimensions and position of visual window now because the ConfigureNotify event lies to us
    core::unique_free_ptr<xcb_get_geometry_reply_t> geometry(xcb_get_geometry_reply(connection,
                                                                                    xcb_get_geometry(connection, window),
                                                                                    nullptr));
    if(!geometry)
      return {};

    core::unique_free_ptr<xcb_query_tree_reply_t> tree(xcb_query_tree_reply(connection,
                                                                            xcb_query_tree(connection, window),
                                                                            nullptr));
    if(!tree)
      return {};

    xcb_translate_coordinates_cookie_t translateCookie = xcb_translate_coordinates(connection,
                                                                                   window,
                                                                                   tree->parent,
                                                                                   geometry->x, geometry->y);

    core::unique_free_ptr<xcb_translate_coordinates_reply_t> translation(xcb_translate_coordinates_reply(connection,
                                                                                                         translateCookie,
                                                                                                         nullptr));
    if(!translation)
      return {};

    return {{translation->dst_x, translation->dst_y}, {geometry->width, geometry->height}};
  }

  xcb_connection_t* xcb::get_connection() const
  {
    return connection;
  }

  xcb_window_t xcb::get_window() const
  {
    return window;
  }

  void xcb::create(const graphics::pixel_position& position,
                   const graphics::pixel_size& size)
  {
    const auto xcb_native_visual = dynamic_cast<native_visual::xcb*>(native_visual.get());
    if(!xcb_native_visual)
    {
      core::debug_print("native_window::xcb can only use native_visual::xcb");
      std::exit(1);
    }

    make_xcb_window(position,
                    size,
                    connection,
                    preferred_screen,
                    xcb_native_visual->visualid(),
                    window);

    native_visual->create_surface(window);
  }

  xcb::xcb(std::unique_ptr<native_visual::base>&& native_visual,
           xcb_connection_t* connection)
    : xcb_data(connection)
    , base(std::move(native_visual))
  {}
}
