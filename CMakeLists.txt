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

cmake_minimum_required(VERSION 3.5)
project(skui)

option(SKUI_USE_SYSTEM_ZLIB "Use system zlib" OFF)
option(SKUI_USE_SYSTEM_LIBEXPAT "Use system libexpat" OFF)
option(SKUI_USE_SYSTEM_LIBPNG "Use system libpng" OFF)
option(SKUI_USE_SYSTEM_GIFLIB "Use system giflib" OFF)
option(SKUI_USE_SYSTEM_LIBJPEG_TURBO "Use system libjpeg-turbo" OFF)
option(SKUI_USE_SYSTEM_SKIA "Use system Skia library" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  set(CMAKE_LINK_FLAGS "-Wl,--gc-sections ${CMAKE_LINK_FLAGS}")
elseif(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  if(NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
      add_compile_options(/wd4503)
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  if(MINGW)
    link_libraries(-lpthread)
  else()
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
    add_compile_options(-Wno-error=unused-command-line-argument)
    link_libraries(-lc++ -lc++abi)
  endif()
endif()

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
    tests/runtime_test.cmake
    tests/compile_test.cmake)

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
