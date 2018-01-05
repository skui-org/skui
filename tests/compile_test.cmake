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

message(STATUS "runtime test: test_dir=${test_dir}, test_name=${test_name}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E remove "${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX}"
                RESULT_VARIABLE exit_code
                ERROR_VARIABLE stderr)

if(NOT 0 EQUAL ${exit_code})
  message(FATAL_ERROR "Could not remove ${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX}:\n${stderr}")
endif()

execute_process(COMMAND "${CMAKE_COMMAND}" --build .. --target "${test_name}"
                RESULT_VARIABLE exit_code
                ERROR_VARIABLE stderr
                OUTPUT_QUIET)

if(NOT 0 EQUAL ${exit_code})
  message(FATAL_ERROR "Could not compile ${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX}:\n${stderr}")
endif()
