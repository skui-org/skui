/**
 * The MIT License (MIT)
 *
 * Copyright © 2018-2020 Ruben Van Boxem
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

#ifndef SKUI_TEST_MOCK_CANVAS_H
#define SKUI_TEST_MOCK_CANVAS_H

#include <graphics/canvas.h++>

namespace skui
{
  namespace test
  {
    struct mock_canvas : public graphics::canvas
    {
    public:
      mock_canvas(graphics::canvas_flags flags = graphics::canvas_flag::none) : canvas(flags) {}
      ~mock_canvas() override = default;

      void draw(const graphics::style::fill&,
                const std::optional<graphics::scalar_bounding_box>&) override {}
      void draw(const graphics::rectangle&,
                const graphics::scalar_position&,
                const std::optional<graphics::scalar_bounding_box>&) override {}
      void draw(const graphics::ellipse&,
                const graphics::scalar_position&,
                const std::optional<graphics::scalar_bounding_box>&) override {}
      void draw(const graphics::text&,
                const graphics::scalar_position&,
                const std::optional<graphics::scalar_bounding_box>&) override {}
      void draw(const graphics::path&,
                const graphics::scalar_position&,
                const std::optional<graphics::scalar_bounding_box>&) override {}

      graphics::scalar_size measure_text(const graphics::text&) const override
      {
        return {};
      }
    };
  }
}
#endif
