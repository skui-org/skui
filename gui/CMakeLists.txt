##
#
# The MIT License (MIT)
#
# Copyright (c) 2017 Ruben Van Boxem
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Common source files
set(gui_src
    icon.h++
    key.h++
    window.h++ window.c++ window_windows.c++ window_xcb.c++
   )

# The library itself
add_library(gui ${gui_src})
target_link_libraries(gui PUBLIC core graphics)

# Platform specific libraries
if(UNIX)
  if(NOT APPLE)
      find_package(X11 REQUIRED)
      target_link_libraries(gui PUBLIC xcb X11-xcb X11)
  endif()
endif()

# Platform specific files
if(NOT WIN32)
  exclude_from_build(main_windows.c++
                     window_windows.c++
                    )
endif()
if(NOT UNIX)
  if(NOT APPLE)
  else()
    exclude_from_build(window_x11.c++
                      )
  endif()
endif()
