/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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
 * OUT OF OR IN CONnECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "test.h++"

#include "gui/mock_canvas.h++"
#include "gui/mock_element.h++"

#include <graphics/bounding_box.h++>
#include <graphics/canvas.h++>

#include <gui/make_element.h++>
#include <gui/layout.h++>

namespace
{
  using skui::test::check;
  using skui::test::mock_canvas;

  struct mock_element : public skui::gui::element
  {
  public:
    mock_element() = default;
    ~mock_element() override = default;

    void draw(skui::graphics::canvas&, const skui::graphics::scalar_position& position) const override
    {
      drawn_positions.push_back(position);
    }

    skui::graphics::scalar_size implicit_size(const skui::graphics::canvas&) const override
    {
      return {1, 1};
    }

    static std::vector<skui::graphics::scalar_position> drawn_positions;
  };
  std::vector<skui::graphics::scalar_position> mock_element::drawn_positions;

  struct mock_layout : public skui::gui::layout
  {
  public:
    mock_layout(skui::gui::element_ptrs children = {}) : layout(std::move(children)) {}
    template<typename... ElementPointerTypes>
    mock_layout(ElementPointerTypes&&... element_pointers)
      : layout(make_element_ptrs(std::forward<ElementPointerTypes>(element_pointers)...))
    {}
    ~mock_layout() override = default;

    skui::graphics::scalar_size implicit_size(const skui::graphics::canvas&) const override
    {
      return {1, 2};
    }

  private:
    std::vector<skui::graphics::scalar_position> calculate_child_offsets(const skui::graphics::canvas&) const override
    {
      return {{1, 1}, {2, 2}, {3, 3}};
    }
  };

  void test_layout_draw_uses_calculate_offsets()
  {
    mock_canvas canvas;
    mock_layout layout(std::make_unique<mock_element>(),
                       std::make_unique<mock_element>(),
                       std::make_unique<mock_element>());

    layout.draw(canvas, {5, 5});

    check(mock_element::drawn_positions == std::vector<skui::graphics::scalar_position>{{6, 6}, {7, 7}, {8, 8}});
  }
}

int main()
{
  test_layout_draw_uses_calculate_offsets();

  return skui::test::exit_code;
}
