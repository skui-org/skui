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
set(graphics_src
    canvas.h++ canvas.c++
    color.h++
    context.h++ context.c++
    drawable.h++
    gradient.h++ gradient.c++
    gradient/linear_gradient.h++ gradient/linear_gradient.c++
    gradient/radial_gradient.h++ gradient/radial_gradient.c++
    gradient/sweep_gradient.h++ gradient/sweep_gradient.c++
    gradient/two_point_conical_gradient.h++ gradient/two_point_conical_gradient.c++
    pixel.h++
    position.h++
    scalar.h++
    shape.h++ shape.c++
    shape/ellipse.h++ shape/ellipse.c++
    shape/label.h++ shape/label.c++
    shape/path.h++ shape/path.c++
    shape/rectangle.h++ shape/rectangle.c++
    size.h++
    skia_canvas.h++ skia_canvas.c++
    skia_context.h++ skia_context.c++
    skia_util.h++ skia_util.c++
   )

# The library itself
add_library(graphics ${graphics_src})
target_link_libraries(graphics PUBLIC core skia)
target_compile_definitions(graphics PRIVATE SKUI_GRAPHICS_INSIDES)
