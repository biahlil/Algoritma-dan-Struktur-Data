#include "circle_module.h"
#include "circle.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

CircleModule::CircleModule() {
  auto slider_radius = Slider("Radius: ", &radius, 1, 10, 1);
  auto slider_point_x = Slider("Point X: ", &point_x, -10, 10, 1);
  auto slider_point_y = Slider("Point Y: ", &point_y, -10, 10, 1);
  auto slider_user_x = Slider("User X: ", &user_x, -10, 10, 1);
  auto slider_user_y = Slider("User Y: ", &user_y, -10, 10, 1);
  auto input_container =
      Container::Vertical({slider_radius, slider_point_x, slider_point_y,
                           slider_user_x, slider_user_y});
  this->container = input_container;
}

ftxui::Element CircleModule::GetOutputElement() {
  Point user = {(double)user_x, (double)user_y};
  Point circle = {(double)point_x, (double)point_y};
  Circle c = {circle, (double)radius};
  double hasil_jarak = distance(&c, &user);
  std::string posisi = CheckPointInCircle(hasil_jarak);
  return vbox(
      {text("Persamaan: (x-" + std::to_string(point_x) + ")^2 + (y-" +
            std::to_string(point_y) + ")^2 = " + std::to_string(radius) + "^2"),
       text("Jarak: " + std::to_string(hasil_jarak)),
       text("Titik : (" + std::to_string(user_x) + ", " +
            std::to_string(user_y) + ")"),
       text("Status Praktikum: " + posisi) | bold | color(Color::Cyan)});
}

void CircleModule::DrawCanvas(ftxui::Canvas &canvas) {
  int center_x = 50;
  int center_y = 50;
  int scale = 2;

  canvas.DrawPointLine(0, center_y, 100, center_y, Color::GrayDark);
  canvas.DrawPointLine(center_x, 0, center_x, 100, Color::GrayDark);

  int draw_px = center_x + (user_x * scale);
  int draw_py = center_y - (user_y * scale);
  canvas.DrawPointCircle(draw_px, draw_py, 1, Color::Cyan);

  int draw_cx = center_x + (point_x * scale);
  int draw_cy = center_y - (point_y * scale);
  canvas.DrawPointCircle(draw_cx, draw_cy, radius * scale, Color::Blue);
}