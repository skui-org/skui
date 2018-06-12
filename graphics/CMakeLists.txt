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

find_package(OpenGL REQUIRED)

# Common source files
set(graphics_src
    canvas.h++ canvas.c++
    color.h++
    context.h++ context.c++
    drawable.h++ drawable.c++
    pixel.h++
    position.h++
    scalar.h++
    scene.h++ scene.c++
    shape.h++ shape.c++
    size.h++
    skia_canvas.h++ skia_canvas.c++
    skia_gl_canvas.h++ skia_gl_canvas.c++
    skia_gl_context.h++ skia_gl_context.c++
    skia_gradient.h++ skia_gradient.c++
    skia_raster_context.h++ skia_raster_context.c++
    skia_raster_canvas.h++ skia_raster_canvas.c++
    skia_utility.h++ skia_utility.c++
    swizzle.h++ swizzle.c++
   )
set(gradient_src
    gradient.h++
    gradient/linear_gradient.h++
    gradient/radial_gradient.h++
    gradient/sweep_gradient.h++
    gradient/two_point_conical_gradient.h++
   )
set(shape_src
    shape/ellipse.h++ shape/ellipse.c++
    shape/path.h++ shape/path.c++
    shape/rectangle.h++ shape/rectangle.c++
    shape/text.h++ shape/text.c++
   )
set(style_src
    style/border.h++
    style/fill.h++
    style/line.h++
    style/spacing.h++
   )

source_group("" FILES ${graphics_src})
source_group(gradient FILES ${gradient_src})
source_group(shape FILES ${shape_src})
source_group(style FILES ${style_src})

# The library itself
add_library(graphics ${graphics_src} ${gradient_src} ${shape_src} ${style_src})
target_link_libraries(graphics PUBLIC core)
target_link_libraries(graphics PRIVATE skia
                                       ${OPENGL_LIBRARIES}
                                       $<$<OR:$<PLATFORM_ID:Windows>,$<PLATFORM_ID:Darwin>>:opengl-api>)
target_compile_definitions(graphics PRIVATE SKUI_GRAPHICS_INSIDES
                                            $<$<PLATFORM_ID:Windows>:NOMINMAX>)
