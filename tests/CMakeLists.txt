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
#

# Boilerplate CMake code
function(runtime_test component test_name)
  add_executable(${test_name} ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})
  add_test(remove/${component}/${test_name} ${CMAKE_COMMAND} -E remove ${component}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})
  add_test(build/${component}/${test_name} ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${test_name})
  add_test(NAME    run/${component}/${test_name}
           COMMAND ${component}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})
  set_tests_properties(run/${component}/${test_name} PROPERTIES DEPENDS build/${component}/${test_name})
  #TODO add intertest dependencies
  #BROKEN Each runtime_test is actually 3 tests, use below to make it one test
#  add_test(${test_dir}/${test_name} ${CMAKE_COMMAND} -E remove ${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX}
#                                 && ${CMAKE_COMMAND} --build --target ${test_name})
#                                 && ${CMAKE_CURRENT_LIST_DIR}/${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})

endfunction()

function(compile_test component test_name)
  add_executable(${test_name} EXCLUDE_FROM_ALL ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})
  add_test(remove/${component}/${test_name} ${CMAKE_COMMAND} -E remove ${component}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})
  add_test(build/${component}/${test_name} ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${test_name})
endfunction()

function(compile_test_library component test_name)
  add_library(${test_name} SHARED EXCLUDE_FROM_ALL ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  set_target_properties(${test_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${component}
                                                RUNTIME_OUTPUT_DIRECTORY ${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})
  add_test(remove/${component}/${test_name} ${CMAKE_COMMAND} -E remove ${component}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})
  add_test(build/${component}/${test_name} ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${test_name})
endfunction()

runtime_test(core value_ptr)
runtime_test(core trackable)
runtime_test(core signal)
runtime_test(core slot)
runtime_test(core property)
runtime_test(core proxy_property)
compile_test(core application)
add_test(NAME run/core/application COMMAND core/application "skui is awesome")
compile_test_library(core library_lib)
runtime_test(core library)
runtime_test(core command)
runtime_test(core command_queue)
runtime_test(core event_loop)
