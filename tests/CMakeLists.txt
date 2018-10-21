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
#

set(test_list_dir ${CMAKE_CURRENT_LIST_DIR})

function(runtime_test component test_name)
  set(test_src ${test_list_dir}/${component}/${test_name}.test.c++)
  source_group("" FILES ${test_src})
  string(REPLACE "/" "_" test_target_name ${test_name})
  add_executable(${test_target_name} ${test_src})
  set_target_properties(${test_target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                                                       RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
                                                       RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
                                                       RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
                                                       RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
                                                       FOLDER tests/${component})
  target_include_directories(${test_target_name} PUBLIC ${test_list_dir} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_target_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_component=${component}
                                                      -Dtest_name=${test_target_name}
                                                      -P ${test_list_dir}/runtime_test.cmake)
endfunction()

function(compile_test component test_name)
  set(test_src ${test_list_dir}/${component}/${test_name}.test.c++)
  source_group("" FILES ${test_src})
  add_executable(${test_name} ${test_src})
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
                                                FOLDER tests/${component})
  target_include_directories(${test_name} PUBLIC ${test_list_dir} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_component=${component}
                                                      -Dtest_name=${test_name}
                                                      -P ${test_list_dir}/compile_test.cmake)
endfunction()

function(compile_test_library component test_name)
  set(test_src ${test_list_dir}/${component}/${test_name}.test.c++)
  source_group("" FILES ${test_src})
  add_library(${test_name} SHARED ${test_src})
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
                                                RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
                                                LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                                                LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
                                                LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}
                                                LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_BINARY_DIR}
                                                LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_BINARY_DIR}
                                                FOLDER tests/${component})
  target_include_directories(${test_name} PUBLIC ${test_list_dir} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_component=${component}}
                                                      -Dtest_name=${test_name}
                                                      -Dtest_binary_dir=}
                                                      -P ${test_list_dir}/compile_test.cmake)
endfunction()

add_custom_target(tests_shared SOURCES
                  test.h++
                  core/property_tests.h++
                  graphics/composite_value_tests.h++
                  gui/mock_canvas.h++
                  gui/mock_element.h++
                  runtime_test.cmake
                  compile_test.cmake
                 )
runtime_test(core value_ptr)
runtime_test(core trackable)
runtime_test(core signal)
runtime_test(core slot)
runtime_test(core property)
runtime_test(core proxy_property)
compile_test(core application)
add_test(NAME run/core/application COMMAND core/application "skui is awesome")
set_tests_properties(run/core/application PROPERTIES DEPENDS core/application)
compile_test_library(core library_lib)
runtime_test(core library)
set_tests_properties(core/library PROPERTIES DEPENDS library_lib)
runtime_test(core command)
runtime_test(core command_queue)
runtime_test(core event_loop)
runtime_test(core bitflag)
compile_test(core arity)
runtime_test(core bounded_property)
runtime_test(core utility)
runtime_test(core utility/bound)
runtime_test(core utility/norm)
runtime_test(core utility/approximate_equal_to)
compile_test(core number_of_bits)
runtime_test(core proxy_map)

runtime_test(graphics position)
runtime_test(graphics size)
runtime_test(graphics swizzle)
compile_test(graphics color)

runtime_test(gui layout)
runtime_test(gui layout/row)
runtime_test(gui layout/column)

compile_test(system environment)
add_test(NAME run/system/environment COMMAND system/environment)
set_tests_properties(run/system/environment PROPERTIES DEPENDS system/environment
                                                       ENVIRONMENT TEST_VARIABLE=skui)
