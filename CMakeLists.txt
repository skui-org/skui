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
# zlib
if(SKUI_USE_PREBUILT_ZLIB)
  add_library(zlib INTERFACE)
  target_include_directories(zlib SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/zlib)
  target_link_libraries(zlib INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -lzlib)
  set(ZLIB_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_ZLIB)
  find_package(ZLIB REQUIRED)
  add_library(zlib INTERFACE)
  target_link_libraries(zlib INTERFACE ZLIB::ZLIB)
endif()
# libexpat
if(SKUI_USE_PREBUILT_LIBEXPAT)
  add_library(expat INTERFACE)
  target_include_directories(expat SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/libexpat)
  target_link_libraries(expat INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -lexpat)
  set(EXPAT_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_LIBEXPAT)
  find_package(EXPAT REQUIRED)
  add_library(expat INTERFACE)
  target_link_libraries(expat INTERFACE EXPAT::EXPAT)
endif()
# libpng
if(SKUI_USE_PREBUILT_LIBPNG)
  add_library(png INTERFACE)
  target_include_directories(png SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/libpng)
  target_link_libraries(png INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -lpng)
  set(PNG_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_LIBPNG)
  find_package(PNG REQUIRED)
  add_library(png INTERFACE)
  target_link_libraries(png INTERFACE PNG::PNG)
endif()
# giflib
if(SKUI_USE_PREBUILT_GIFLIB)
  add_library(gif INTERFACE)
  target_include_directories(gif SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/giflib)
  target_link_libraries(gif INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -lgif)
  set(GIF_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_GIFLIB)
  find_package(GIF REQUIRED)
  add_library(gif INTERFACE)
  target_include_directories(gif SYSTEM INTERFACE ${GIF_INCLUDE_DIR})
  target_link_libraries(gif INTERFACE ${GIF_LIBRARIES})
endif()
if(SKUI_USE_PREBUILT_LIBJPEG_TURBO)
  add_library(jpeg-turbo INTERFACE)
  target_include_directories(jpeg-turbo SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/libjpeg-turbo)
  target_link_libraries(jpeg-turbo INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -ljpeg-turbo)
  set(LibJpegTurbo_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_LIBJPEG_TURBO)
  find_package(LibJpegTurbo REQUIRED)
  add_library(jpeg-turbo INTERFACE)
  target_include_directories(jpeg-turbo SYSTEM INTERFACE ${LibJpegTurbo_INCLUDE_DIRS})
  target_link_libraries(jpeg-turbo INTERFACE ${LibJpegTurbo_LIBRARIES})
endif()
if(SKUI_USE_PREBUILT_SKIA)
  add_library(skia INTERFACE)
  target_include_directories(skia SYSTEM INTERFACE
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/android
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/atlastext
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/c
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/codec
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/config
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/core
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/docs
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/effects
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/encode
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/gpu
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/gpu/gl
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/gpu/mock
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/gpu/mtl
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/gpu/vk
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/pathops
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/ports
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/svg
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/utils
      ${SKUI_PREBUILT_3RDPARTY_PATH}/skia/include/utils/mac)
  target_link_libraries(skia INTERFACE -L${SKUI_PREBUILT_3RDPARTY_PATH} -lskia png expat zlib gif jpeg-turbo)
  if(WIN32)
    target_link_libraries(skia INTERFACE usp10)
  elseif(APPLE)
    target_link_libraries(skia INTERFACE "-framework CoreText"
                                         "-framework CoreGraphics"
                                         "-framework Foundation")
  elseif(UNIX AND NOT MINGW)
    find_package(Freetype REQUIRED)
    target_link_libraries(skia INTERFACE ${FREETYPE_LIBRARIES} fontconfig)
  endif()
  set(SKIA_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_SKIA)
  message(WARNING "Using system Skia library currently not supported")
endif()
# Boost
if(SKUI_USE_PREBUILT_BOOST)
  add_library(boost INTERFACE)
  target_include_directories(boost SYSTEM INTERFACE ${SKUI_PREBUILT_3RDPARTY_PATH}/boost)
  set(Boost_FOUND TRUE)
elseif(SKUI_USE_SYSTEM_BOOST)
  find_package(Boost 1.66 REQUIRED)
  add_library(boost INTERFACE)
  target_include_directories(boost SYSTEM INTERFACE ${Boost_INCLUDE_DIRS})
endif()

# For those not requested or found as prebuilt or system libraries
add_subdirectory(3rdparty)

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
