/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2018 Ruben Van Boxem
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

/*
 * Widget Gallery
 * Program showing off all skui widgets.
 */

#include <core/application.h++>

#include <graphics/color.h++>

#include <graphics/gradient/sweep_gradient.h++>

#include <graphics/scene.h++>

#include <graphics/shape/ellipse.h++>
#include <graphics/shape/rectangle.h++>
#include <graphics/shape/text.h++>

#include <gui/element/graphics_view.h++>
#include <gui/window.h++>

#include <memory>

int main(int argc, char* argv[])
{
  using skui::core::application;

  using namespace skui::graphics;

  application app(argc, argv, "Widget Gallery");

  skui::graphics::scene scene;
  scene.background_color = colors::white;

  auto square = std::make_unique<rectangle>(scalar_size{140, 140});
  square->fill.color = colors::red;
  square->border.thickness = 20; // black by default

  auto marker = std::make_unique<rectangle>(scalar_size{140,140});
  marker->fill.color = colors::transparent;
  marker->border.thickness = 1;
  marker->border.color = colors::green;

  auto circle = std::make_unique<ellipse>(scalar_size{140, 140});
  const scalar_position center{70, 70};
  const std::vector<color> rainbow{colors::cyan,
                                   colors::magenta,
                                   colors::yellow,
                                   colors::cyan};
  circle->fill.gradient = std::make_unique<sweep_gradient>(center, rainbow);

  auto text_label = std::make_unique<text>("Hello Skui!");
  text_label->fill.color = colors::black;

  scene.drawables.emplace_back(scalar_position{10, 10}, std::move(square));
  scene.drawables.emplace_back(scalar_position{10.5, 10.5}, std::move(marker));
  scene.drawables.emplace_back(scalar_position{150, 150}, std::move(circle));
  scene.drawables.emplace_back(scalar_position{300, 300}, std::move(text_label));

  skui::gui::window window;
  window.element = std::make_unique<skui::gui::graphics_view>(scene);
  window.show();

  return app.execute();
}
