##
#
# The MIT License (MIT)
#
# Copyright © 2018-2019 Ruben Van Boxem
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
    color.h++
    declaration_block.h++
    length.h++ length.c++
    parser.h++ parser.c++
    rule_set.h++
    selector.h++ selector.c++
    time.h++
    timing_function.h++ timing_function.c++
   )
set(properties_src
    property.h++ property.c++
    property/align_content.h++
    property/align_items.h++
    property/align_self.h++
    property/animation_direction.h++
    property/animation_fill_mode.h++
    property/animation_iteration_count.h++
    property/animation_play_state.h++
    property/backface_visibility.h++
    property/background.h++
    property/border.h++
   )
set(grammar_src
    grammar.h++ grammar.c++
    grammar/as.h++
    grammar/declaration_block.h++
    grammar/property.h++ grammar/property.c++
    grammar/align_content.h++ grammar/align_content.c++
    grammar/align_items.h++ grammar/align_items.c++
    grammar/align_self.h++ grammar/align_self.c++
    grammar/background.h++ grammar/background.c++
    grammar/backface_visibility.h++ grammar/backface_visibility.c++
    grammar/color.h++ grammar/color.c++
    grammar/length.h++ grammar/length.c++
    grammar/make_property.h++
    grammar/numeric.h++
    grammar/property_symbols_table.h++
    grammar/quoted_string.h++
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
   )

source_group(css FILES ${css_src})
source_group(grammar FILES ${grammar_src})
source_group(properties FILES ${properties_src})

add_library(css ${css_src} ${grammar_src} ${properties_src} ${misc})
target_link_libraries(css PUBLIC core boost)
