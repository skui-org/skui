##
#
# The MIT License (MIT)
#
# Copyright © 2017-2018 Ruben Van Boxem
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

cmake_minimum_required(VERSION 3.8)
project(skui)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(toolchain_options)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(SKUI_USE_SYSTEM_ZLIB "Use system zlib" OFF)
option(SKUI_USE_SYSTEM_LIBEXPAT "Use system libexpat" OFF)
option(SKUI_USE_SYSTEM_LIBPNG "Use system libpng" OFF)
option(SKUI_USE_SYSTEM_GIFLIB "Use system giflib" OFF)
option(SKUI_USE_SYSTEM_LIBJPEG_TURBO "Use system libjpeg-turbo" OFF)
option(SKUI_USE_SYSTEM_SKIA "Use system Skia library" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Boilerplate
function(exclude_from_build)
  set_source_files_properties(${ARGV} PROPERTIES HEADER_FILE_ONLY TRUE)
endfunction()

# Miscellaneous files
add_custom_target(miscellaneous SOURCES
    README.md
    TODO.md
    LICENSE
    .gitignore
    .gitmodules
    appveyor.yml
    .travis.yml
    ci/setup_cmake.sh
    ci/setup_libcxx.sh
    ci/setup_ninja.sh
    cmake/toolchain_options.cmake
    )

# Skia and its dependencies
add_subdirectory(3rdparty)

# skui itself
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(gui)
add_subdirectory(opengl)

# skui examples
add_subdirectory(examples)

# skui tests
enable_testing()
add_subdirectory(tests)
