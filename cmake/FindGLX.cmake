##
#
# The MIT License (MIT)
#
# Copyright © 2017-2019 Ruben Van Boxem
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

#
# FindGLX
#
# This will will define the following variables:
#
# GLX_FOUND - system has GLX
# GLX_INCLUDE_DIRS - the GLX include directory
# GLX_LIBRARIES - the GLX libraries
#
# and the following imported targets::
#
#   GLX - The GLX library

if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_GLX glx QUIET)
endif()

find_path(GLX_INCLUDE_DIR NAMES GL/glx.h
                          PATHS ${PC_GLX_INCLUDEDIR})
find_library(GLX_LIBRARY NAMES GL
                         PATHS ${PC_GLX_LIBDIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLX
                                  REQUIRED_VARS GLX_LIBRARY GLX_INCLUDE_DIR)

if(GLX_FOUND)
  set(GLX_LIBRARIES ${GLX_LIBRARY})
  set(GLX_INCLUDE_DIRS ${GLX_INCLUDE_DIR})

  if(NOT TARGET GLX)
    add_library(GLX UNKNOWN IMPORTED)
    set_target_properties(GLX PROPERTIES
                              IMPORTED_LOCATION "${GLX_LIBRARY}"
                              INTERFACE_INCLUDE_DIRECTORIES "${GLX_INCLUDE_DIR}")
  endif()
endif()

mark_as_advanced(GLX_INCLUDE_DIR GLX_LIBRARY)
