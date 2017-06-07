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
set(core_src
    application.h++ application.c++ application_windows.c++ application_unix.c++
    bitflag.h++
    command.h++
    command_queue.h++ command_queue.c++
    debug.h++
    event_loop.h++ event_loop.c++
    library.h++ library.c++ library_windows.c++ library_unix.c++
    path.h++
    property.h++
    proxy_property.h++
    signal.h++
    slot.h++
    string.h++ string.c++
    trackable.h++ trackable.c++
    utility.h++ utility.c++
    value_ptr.h++
    )

# Platform-specific files
if(NOT WIN32)
  exclude_from_build(application_windows.c++ library_windows.c++)
endif()
if(NOT UNIX)
  exclude_from_build(library_unix.c++ application_unix.c++)
  if(NOT APPLE)
  endif()
endif()

# Missing C++17 features
if(MINGW)
  find_package(Boost COMPONENTS regex system filesystem REQUIRED)
endif()

# The library itself
add_library(core ${core_src})
target_include_directories(core PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
target_compile_definitions(core PUBLIC $<$<CONFIG:Debug>:SKUI_DEBUG>)
target_link_libraries(core PUBLIC $<$<PLATFORM_ID:Linux>:-pthread>
                                  $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Intel>>,$<NOT:$<PLATFORM_ID:Windows>>>:-lstdc++fs>
                                  $<$<CXX_COMPILER_ID:Clang>:-lc++experimental>
                                  $<$<NOT:$<PLATFORM_ID:Windows>>:-ldl>)
if(MINGW)
  target_link_libraries(core PUBLIC Boost::system Boost::regex Boost::filesystem)
endif()

