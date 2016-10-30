##
#
# The MIT License (MIT)
#
# Copyright (c) 2016 Ruben Van Boxem
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
set(core_src
    application.h++ application.c++ application_windows.c++ application_unix.c++
    debug.h++
    property.h++
    signal.h++
    string.h++ string.c++
    )

# Platform-specific files
if(NOT WIN32)
  exclude_from_build(application_windows.c++)
endif()
if(NOT UNIX)
  if(NOT APPLE)
  else()
    exclude_from_build(application_unix.c++)
  endif()
endif()

# The library itself
add_library(core ${core_src})
set_target_properties(core PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR})
target_compile_definitions(core PRIVATE $<$<CONFIG:Debug>:SKUI_DEBUG>)
