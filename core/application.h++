/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2020 Ruben Van Boxem
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
 * Application
 * Basic application parameters and information.
 * Singleton. The one and only.
 */

#ifndef SKUI_CORE_APPLICATION_H
#define SKUI_CORE_APPLICATION_H

#include "core/event_loop.h++"
#include "core/property.h++"
#include "core/string.h++"
#include "core/trackable.h++"

#include <cstdlib>
#include <vector>

namespace skui::core
{
  class application
  {
  public:
    application(int argc, char* argv[], string name = "");
    ~application();

    const std::vector<string> commandline_arguments;

    property<string> name;

    signal<> about_to_quit;

    static application& instance();

    int execute();
    void quit(int exit_code = EXIT_SUCCESS);

    const std::vector<string>& arguments() const;

  private:
    core::event_loop event_loop;
  };
}

#endif
