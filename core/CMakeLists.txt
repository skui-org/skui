##
#
# The MIT License (MIT)
#
# Copyright © 2017-2020 Ruben Van Boxem
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

set(core_src
    application.h++ application.c++
    bitflag.h++
    bounded_property.h++
    command.h++ command.c++
    command_queue.h++ command_queue.c++
    debug.h++
    event_loop.h++ event_loop.c++
    library.h++ library.c++ library_windows.c++ library_unix.c++
    path.h++
    property.h++
    proxy_map.h++
    proxy_property.h++
    signal.h++
    slot.h++
    string.h++
    trackable.h++ trackable.c++
    utility.h++ utility.c++
    value_ptr.h++
   )
set(traits_src
    traits/are_convertible.h++
    traits/are_same.h++
    traits/arity.h++
    traits/number_of_bits.h++
   )
set(utility_src
    utility/approximate_equal_to.h++
    utility/bound.h++
    utility/norm.h++
   )
source_group("" FILES ${core_src})
source_group(traits FILES ${traits_src})
source_group(utility FILES ${utility_src})

# Platform-specific files
if(NOT WIN32)
  exclude_from_build(
                     library_windows.c++
                    )
endif()
if(NOT UNIX)
  exclude_from_build(
                     library_unix.c++
                    )
  if(NOT APPLE)
  endif()
endif()

add_library(core
            ${core_src}
            ${traits_src}
            ${utility_src})
target_include_directories(core PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
target_compile_definitions(core PUBLIC $<$<CONFIG:Debug>:SKUI_DEBUG>
                                       $<$<PLATFORM_ID:Windows>:NOMINMAX>)
target_link_libraries(core PUBLIC $<$<PLATFORM_ID:Linux>:-pthread>
                                  $<$<CXX_COMPILER_ID:GNU>:-lstdc++fs>
                                  $<$<AND:$<PLATFORM_ID:Windows>,$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<STREQUAL:"x${CMAKE_CXX_SIMULATE_ID}","xMSVC">>>>:-lstdc++fs>
                                  $<$<AND:$<NOT:$<PLATFORM_ID:Windows>>,$<AND:$<CXX_COMPILER_ID:Clang>,$<AND:$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,7>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9>>>>:-lc++fs>
                                  $<$<AND:$<NOT:$<PLATFORM_ID:Windows>>,$<AND:$<CXX_COMPILER_ID:Clang>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,7>>>:-lc++experimental>
                                  $<$<NOT:$<PLATFORM_ID:Windows>>:-ldl>)
