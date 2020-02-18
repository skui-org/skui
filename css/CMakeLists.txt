##
#
# The MIT License (MIT)
#
# Copyright © 2018-2020 Ruben Van Boxem
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

set(css_src
    angle.h++
    color.h++
    color_stop.h++
    declaration_block.h++
    length.h++
    ostream.h++ ostream.c++
    parser.h++ parser.c++
    position.h++
    rule_set.h++
    selector.h++ selector.c++
    time.h++
    timing_function.h++
   )
set(properties_src
    property.h++
    property/align_content.h++
    property/align_items.h++
    property/align_self.h++
    property/animation.h++
    property/conic_gradient.h++
    property/backface_visibility.h++
    property/background.h++
    property/background_gradient.h++
    property/border.h++
    property/box_decoration_break.h++
    property/box_shadow.h++
    property/linear_gradient.h++
    property/radial_gradient.h++
   )
set(grammar_src
    grammar.h++ grammar.c++
    grammar/angle.h++
    grammar/as.h++
    grammar/declaration_block.h++
    grammar/property.h++ grammar/property.c++
    grammar/align_content.h++ grammar/align_content.c++
    grammar/align_items.h++ grammar/align_items.c++
    grammar/align_self.h++ grammar/align_self.c++
    grammar/animation.h++ grammar/animation.c++
    grammar/background.h++ grammar/background.c++
    grammar/backface_visibility.h++ grammar/backface_visibility.c++
    grammar/box_decoration_break.h++ grammar/box_decoration_break.c++
    grammar/box_shadow.h++
    grammar/color.h++ grammar/color.c++
    grammar/color_stop.h++
    grammar/conic_gradient.h++
    grammar/length.h++ grammar/length.c++
    grammar/linear_gradient.h++ grammar/linear_gradient.c++
    grammar/make_property.h++
    grammar/numeric.h++
    grammar/position.h++ grammar/position.c++
    grammar/property_symbols_table.h++
    grammar/quoted_string.h++
    grammar/radial_gradient.h++ grammar/radial_gradient.c++
    grammar/repeating.h++
    grammar/semantic/convert_to.h++
    grammar/semantic/repeat_value.h++
    grammar/semantic/reset_value.h++
    grammar/semantic_checks.h++
    grammar/semantic_factory.h++
    grammar/semantic_math.h++
    grammar/time.h++
    grammar/timing_function.h++ grammar/timing_function.c++
    grammar/url.h++
    grammar/x3_stdvariant.h++
   )
set(misc
    units.md
    README.md
   )

source_group(css FILES ${css_src})
source_group(grammar FILES ${grammar_src})
source_group(properties FILES ${properties_src})

add_library(css ${css_src} ${grammar_src} ${properties_src} ${misc})
target_link_libraries(css PUBLIC core boost)
