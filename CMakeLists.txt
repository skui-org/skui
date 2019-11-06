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

cmake_minimum_required(VERSION 3.13)
project(skui)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(toolchain_options)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 3rdparty dependencies
option(SKUI_USE_PREBUILT_3RDPARTY "Use a prebuilt 3rdparty package" OFF)
set(SKUI_PREBUILT_3RDPARTY_PATH CACHE STRING "NOTSET")
option(SKUI_USE_PREBUILT_ZLIB "Use a prebuilt zlib" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_LIBEXPAT "Use a prebuilt libexpat" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_LIBPNG "Use a prebuilt libpng" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_GIFLIB "Use a prebuilt giflib" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_LIBJPEG_TURBO "Use a prebuilt libjpeg-turbo" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_SKIA "Use a prebuilt Skia" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_PREBUILT_BOOST "Use a prebuilt Boost" ${SKUI_USE_PREBUILT_3RDPARTY})
option(SKUI_USE_SYSTEM_ZLIB "Use system zlib" OFF)
option(SKUI_USE_SYSTEM_LIBEXPAT "Use system libexpat" OFF)
option(SKUI_USE_SYSTEM_LIBPNG "Use system libpng" OFF)
option(SKUI_USE_SYSTEM_GIFLIB "Use system giflib" OFF)
option(SKUI_USE_SYSTEM_LIBJPEG_TURBO "Use system libjpeg-turbo" OFF)
option(SKUI_USE_SYSTEM_SKIA "Use system Skia library" OFF)
option(SKUI_USE_SYSTEM_BOOST "Use system Boost library" OFF)

include(3rdparty_options)

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
    ci/setup_lcov.sh
    ci/setup_libcxx.sh
    ci/setup_ninja.sh
    cmake/3rdparty_options.cmake
    cmake/toolchain_options.cmake
    scripts/update_copyright.sh
    )

# skui itself
add_subdirectory(core)
add_subdirectory(css)
add_subdirectory(graphics)
add_subdirectory(gui)
add_subdirectory(opengl)
add_subdirectory(system)

# skui examples
add_subdirectory(examples)

# skui tests
enable_testing()
add_subdirectory(tests)
