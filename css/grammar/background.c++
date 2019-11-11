/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2019 Ruben Van Boxem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "css/grammar/background.h++"

#include "css/property/background.h++"

namespace skui::css::grammar
{
  background_repeat_table::background_repeat_table()
  {
    add("repeat", background_repeat::repeat)
       ("repeat-x", background_repeat::repeat_x)
       ("repeat-y", background_repeat::repeat_y)
       ("no-repeat", background_repeat::no_repeat)
       ("space", background_repeat::space)
       ("round", background_repeat::round)
       ;
  }

  background_origin_table::background_origin_table()
  {
    add("padding-box", background_origin::padding_box)
       ("border-box", background_origin::border_box)
       ("content-box", background_origin::content_box)
       ;
  }

  background_clip_table::background_clip_table()
  {
    add("border-box", background_clip::border_box)
       ("padding-box", background_clip::padding_box)
       ("content-box", background_clip::content_box)
       ("text", background_clip::text)
       ;
  }

  background_attachment_table::background_attachment_table()
  {
    add("scroll", background_attachment::scroll)
       ("fixed", background_attachment::fixed)
       ("local", background_attachment::local)
        ;
  }

  background_size_keyword_table::background_size_keyword_table()
  {
    add("cover", background_size_keyword::cover)
       ("contain", background_size_keyword::contain)
       ;
  }

}
