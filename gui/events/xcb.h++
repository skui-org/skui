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
 * Event handling implementation for XCB.
 */

#ifndef SKUI_GUI_EVENTS_XCB_H
#define SKUI_GUI_EVENTS_XCB_H

#include "gui/events.h++"

#include <core/utility.h++>

#include <xcb/xcb.h>

namespace skui
{
  namespace gui
  {
    namespace events
    {
      class xcb : public base
      {
      public:
        xcb(gui::window& window);
        ~xcb() override;

        void exec() override;

      private:
        xcb_connection_t* connection;
        xcb_window_t xcb_window;

        core::unique_free_ptr<xcb_intern_atom_reply_t> wm_delete_window;
      };
    }
  }
}

#endif
