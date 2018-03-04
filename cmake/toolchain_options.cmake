##
#
# The MIT License (MIT)
#
# Copyright © 2018 Ruben Van Boxem
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

# Compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  if(NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
      add_compile_options(/wd4503 /std:c++latest)
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  if(MINGW)
    link_libraries(-lpthread)
  else()
    add_compile_options(-Wno-error=unused-command-line-argument)
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
  endif()
endif()

OPTION(GC_SECTIONS "Enable function and data sections generation for the compiler, and also remove unused sections on link" ON)
OPTION(SPLIT_DEBUG "Split debug info from the rest of the binaries. This should improve link time")

if(GC_SECTIONS)
  if(MINGW OR UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
  endif()

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
endif()

if(SPLIT_DEBUG)
  if(NOT MINGW AND UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gsplit-dwarf")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gsplit-dwarf")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--gdb-index")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--gdb-index")
  endif()
endif()
