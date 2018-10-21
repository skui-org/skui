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

runtime_test(core value_ptr)
runtime_test(core trackable)
runtime_test(core signal)
runtime_test(core slot)
runtime_test(core property)
runtime_test(core proxy_property)
compile_test(core application)
add_test(NAME run/core/application COMMAND application "skui is awesome")
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
