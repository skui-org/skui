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
#

function(runtime_test component test_name)
  set(test_src ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  source_group("" FILES ${test_src})
  add_executable(${test_name} ${test_src})
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${component}
                                                FOLDER tests/${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_dir=${component}
                                                      -Dtest_name=${test_name}
                                                      -P ${CMAKE_CURRENT_LIST_DIR}/runtime_test.cmake)
endfunction()

function(compile_test component test_name)
  set(test_src ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  source_group("" FILES ${test_src})
  add_executable(${test_name} ${test_src})
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${component}
                                     FOLDER tests/${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_dir=${component}
                                                      -Dtest_name=${test_name}
                                                      -P ${CMAKE_CURRENT_LIST_DIR}/compile_test.cmake)
endfunction()

function(compile_test_library component test_name)
  set(test_src ${component}/${test_name}.c++ ${CMAKE_CURRENT_LIST_DIR}/test.h++)
  source_group("" FILES ${test_src})
  add_library(${test_name} SHARED ${test_src})
  set_target_properties(${test_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${component}
                                                LIBRARY_OUTPUT_DIRECTORY_DEBUG ${component}
                                                LIBRARY_OUTPUT_DIRECTORY_RELEASE ${component}
                                                LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${component}
                                                LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${component}
                                                RUNTIME_OUTPUT_DIRECTORY ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${component}
                                                RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${component}
                                                FOLDER tests/${component})
  target_include_directories(${test_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_dir=${component}
                                                      -Dtest_name=${test_name}
                                                      -P ${CMAKE_CURRENT_LIST_DIR}/compile_test.cmake)
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
runtime_test(core bitflag)
compile_test(core arity)
