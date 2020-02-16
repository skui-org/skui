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
#

set(test_list_dir ${CMAKE_CURRENT_LIST_DIR})

function(runtime_test component test_name)
  set(test_src ${test_list_dir}/${component}/${test_name}.test.c++)
  source_group("" FILES ${test_src})
  string(REPLACE "/" "." test_target_name "test.${component}.${test_name}")
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
  string(REPLACE "/" "." test_target_name "test.${component}.${test_name}")
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
                                                      -P ${test_list_dir}/compile_test.cmake)
endfunction()

function(compile_test_library component test_name)
  set(test_src ${test_list_dir}/${component}/${test_name}.test.c++)
  source_group("" FILES ${test_src})
  string(REPLACE "/" "." test_target_name "test.${component}.${test_name}")
  add_library(${test_target_name} SHARED ${test_src})
  set_target_properties(${test_target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
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
  target_include_directories(${test_target_name} PUBLIC ${test_list_dir} ${PROJECT_SOURCE_DIR})
  target_link_libraries(${test_target_name} ${component})

  add_test(${component}/${test_name} ${CMAKE_COMMAND} -Dtest_component=${component}}
                                                      -Dtest_name=${test_target_name}
                                                      -P ${test_list_dir}/compile_test.cmake)
endfunction()

set(shared_src
    test.h++
    core/property_tests.h++
    core/types.h++
    css/test_rule.h++
    graphics/composite_value_tests.h++
    gui/mock_canvas.h++
    gui/mock_element.h++
    runtime_test.cmake
    compile_test.cmake
   )
add_custom_target(tests_shared SOURCES
                  ${shared_src}
                 )
source_group("" FILES ${shared_src})

add_subdirectory(core)
add_subdirectory(css)
add_subdirectory(graphics)
add_subdirectory(gui)
add_subdirectory(system)
