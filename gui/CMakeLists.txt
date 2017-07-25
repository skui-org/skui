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

find_package(XCB COMPONENTS XCB AUX)
find_package(X11_XCB)
find_package(X11)
find_package(GLX)
find_package(EGL)

# Common source files
set(gui_src
    events.h++ events.c++ events_linux.c++ events_windows.c++
    events/win32.h++ events/win32.c++
    events/xcb.h++ events/xcb.c++
    icon.h++
    key.h++
    main_windows.c++
    native_window.h++ native_window.c++ native_window_windows.c++ native_window_linux.c++
    native_window/win32.h++ native_window/win32.c++
    native_window/xcb.h++ native_window/xcb.c++
    native_window/xlib.h++ native_window/xlib.c++
    native_visual.h++ native_visual.c++
    native_visual/egl.h++ native_visual/egl.c++
    native_visual/glx.h++ native_visual/glx.c++
    native_visual/wgl.h++ native_visual/wgl.c++
    native_visual/win32.h++ native_visual/win32.c++
    native_visual/xcb.h++ native_visual/xcb.c++
    window.h++ window.c++ window_windows.c++ window_xcb.c++
    window_flags.h++
   )

# The library itself
add_library(gui ${gui_src})
target_link_libraries(gui PUBLIC core graphics)

# Platform specific files and libraries
if(NOT WIN32)
  exclude_from_build(events/win32.h++ events/win32.c++
                     events_windows.c++
                     main_windows.c++
                     native_window/win32.h++ native_window/win32.c++
                     native_visual/wgl.h++ native_visual/wgl.c++
                     native_visual/win32.h++ native_visual/win32.c++
                     native_window_windows.c++
                     window_windows.c++)
endif()
if(NOT APPLE)
  exclude_from_build(events/appkit.h++ events/appkit.c++
                     events/uikit.h++ events/uikit.c++
                     native_window/appkit.h++ native_window/appkit.c++
                     native_window/uikit.h++ native_window/uikit.c++
                     native_visual/cgl.h++ native_visual/cgl.c++
                     native_window_macosx.c++)
endif()
if(NOT UNIX OR APPLE)
  exclude_from_build(events/xcb.h++ events/xcb.c++
                     events_linux.c++
                     native_visual/glx.h++ native_visual/glx.c++
                     native_visual/xcb.h++ native_visual/xcb.c++
                     native_visual_linux.c++
                     native_window/xcb.h++ native_window/xcb.c++
                     native_window/xlib.h++ native_window/xlib.c++
                     native_window_linux.c++
                     window_xcb.c++)
endif()

if(XCB_FOUND)
  target_link_libraries(gui PUBLIC XCB::XCB XCB::AUX)
else()
  exclude_from_build(events/xcb.h++ events/xcb.c++
                     native_window/xcb.h++ native_window/xcb.c++
                     native_visual/xcb.h++ native_visual/xcb.c++)
endif()

if(GLX_FOUND)
  target_link_libraries(gui PUBLIC GLX)
else()
  exclude_from_build(native_visual/glx.h++ native_visual/glx.c++)
endif()

if(EGL_FOUND)
  target_link_libraries(gui PUBLIC EGL::EGL)
else()
  exclude_from_build(native_visual/egl.h++ native_visual/egl.c++)
endif()

if(X11_FOUND AND X11_XCB_FOUND)
  target_link_libraries(gui PUBLIC ${X11_LIBRARIES} X11::XCB)
else()
  exclude_from_build(native_window/xlib.h++ native_window/xlib.c++)
endif()
