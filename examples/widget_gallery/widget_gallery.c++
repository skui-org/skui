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
#include <core/debug.h++>

#include <graphics/color.h++>

#include <graphics/gradient/sweep_gradient.h++>

#include <graphics/scene.h++>

#include <graphics/shape/ellipse.h++>
#include <graphics/shape/rectangle.h++>
#include <graphics/shape/text.h++>

#include <gui/element/graphics_view.h++>
#include <gui/element/label.h++>
#include <gui/element/spacer.h++>
#include <gui/layout/column.h++>
#include <gui/window.h++>

#include <memory>

skui::graphics::scene setup_graphics_scene()
{
  using namespace skui::graphics;

  scene scene;

  scene.background_color = colors::ghost_white;

  auto square = std::make_unique<rectangle>(scalar_size{140, 140});
  square->fill = colors::red;
  square->border.thickness = 2;
  square->border.radius = 5;
  square->border.color = colors::black;

  auto circle = std::make_unique<ellipse>(scalar_size{140, 140});
  const scalar_position center{70, 70};
  const std::vector<color> rainbow{colors::cyan,
                                   colors::magenta,
                                   colors::yellow,
                                   colors::cyan};
  circle->fill = sweep_gradient{center, rainbow};

  auto text_label = std::make_unique<text>("Hello Skui!");
  text_label->fill = colors::black;

  scene.drawables.emplace_back(scalar_position{10, 10}, std::move(square));
  scene.drawables.emplace_back(scalar_position{150, 150}, std::move(circle));
  scene.drawables.emplace_back(scalar_position{300, 300}, std::move(text_label));

  return scene;
}

auto make_label(const char* text)
{
  auto label = std::make_unique<skui::gui::label>(text);
  label->border.thickness = 1;
  label->border.color = skui::graphics::colors::blue;
  label->border.radius = 5;
  label->background = skui::graphics::colors::red;
  label->fill = skui::graphics::colors::black;
  //label->font.size = 36;

  return label;
}

auto make_spacer(const skui::graphics::scalar_size& size)
{
  auto spacer = std::make_unique<skui::gui::spacer>(size);
  return spacer;
}

void setup_input_debugging(skui::gui::window& window)
{
  using skui::core::debug_print;
  using skui::gui::input::button;
  using skui::gui::input::scroll;

  window.pointer.pressed.connect([](button button) { debug_print("Button press: ", button, '\n'); });
  window.pointer.released.connect([](button button) { debug_print("Button release: ", button, '\n'); });
  window.pointer.clicked.connect([](button button) { debug_print("Button click: ", button, '\n'); });
  window.pointer.scroll.connect([](scroll scroll) { debug_print("Scrolled: ", scroll, '\n'); });
}

int main(int argc, char* argv[])
{
  skui::gui::element::show_invisible = true;

  using skui::core::application;

  application app{argc, argv, "Widget Gallery"};

  skui::gui::window window{{0,0}, {200, 200}};

  auto scene = setup_graphics_scene();
  auto view = std::make_unique<skui::gui::graphics_view>(scene);
  view->size = skui::graphics::scalar_size{400, 320};

  auto column = std::make_unique<skui::gui::column>(std::make_unique<skui::gui::spacer>(skui::graphics::scalar_size{2, 3}),
                                                    std::make_unique<skui::gui::spacer>(skui::graphics::scalar_size{3, 2}),
                                                    std::make_unique<skui::gui::spacer>(skui::graphics::scalar_size{2, 3}),
                                                    make_label("mHello SkUI!y"),
                                                    make_label("This is SkUI's first layout.w"),
                                                    std::move(view));
  window.element = std::move(column);

  setup_input_debugging(window);

  window.show();

  return app.execute();
}
