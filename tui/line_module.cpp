#include "line_module.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "line.h"
#include <cmath>
using namespace ftxui;

LineModule::LineModule() {
  // input sesuai soal
  auto slider_a = Slider("A:", &line_a, -10, 10,
                         1); // (label, reference ke variabel, min, max, step)
  auto slider_b = Slider("B:", &line_b, -10, 10, 1);
  auto slider_c = Slider("C:", &line_c, -10, 10, 1);
  auto slider_x = Slider("X:", &point_x, -10, 10, 1);
  auto slider_y = Slider("Y:", &point_y, -10, 10, 1);

  // Masukkan ke dalam container biar bisa navigasi keyboard
  auto input_container = Container::Vertical({
      slider_a,
      slider_b,
      slider_c,
      slider_x,
      slider_y,
  });
  this->container = input_container;
}

ftxui::Element LineModule::GetOutputElement() {
  // logika dari setiap soal ada di file line.cpp
  Line l = {(double)line_a, (double)line_b, (double)line_c};
  Point p = {(double)point_x, (double)point_y};
  double hasil_substitusi = gradient(&l, &p);
  std::string posisi = CheckPointPosition(hasil_substitusi);
  return vbox(
      {text("Persamaan: " + std::to_string(line_a) + "x + " +
            std::to_string(line_b) + "y + " + std::to_string(line_c) + " = 0"),
       text("Titik: (" + std::to_string(point_x) + ", " +
            std::to_string(point_y) + ")"),
       text("Hasil Hitung (Gradient): " + std::to_string(hasil_substitusi)),
       text("Status Praktikum: " + posisi) | bold | color(Color::Cyan)});
}

void LineModule::DrawCanvas(ftxui::Canvas &canvas) {
  // Kita asumsikan titik (0,0) kartesian ada di (50,50) kanvas.
  // Skala zoom = 2 (Jadi nilai di canvas itu 2x dari nilai slider biar lebih
  // kelihatan)
  int center_x = 50;
  int center_y = 50;
  int scale = 2;

  // Gambar Sumbu X dan Y (Opsional, biar bagus)
  canvas.DrawPointLine(0, center_y, 100, center_y, Color::GrayDark); // Sumbu X
  canvas.DrawPointLine(center_x, 0, center_x, 100, Color::GrayDark); // Sumbu Y

  // Gambar Titik User
  int draw_px = center_x + (point_x * scale);
  int draw_py =
      center_y - (point_y * scale); // Minus karena Y terminal ke bawah
  canvas.DrawPointCircle(draw_px, draw_py, 1, Color::Cyan);

  // Gambar Garis ax + by + c = 0
  if (line_a == 0 && line_b == 0) {
    // Bukan garis, jangan gambar apa-apa
  }
  // Jika garis lebih mendatar
  else if (std::abs(line_b) >= std::abs(line_a)) {
    // Pakai jarak -10 sampai 10 (karena jika 20 dan -20 kadang bisa lebih dari
    // canvas)
    double math_x1 = -10.0;
    double math_y1 = -((line_a * math_x1) + line_c) / (double)line_b;

    double math_x2 = 10.0;
    double math_y2 = -((line_a * math_x2) + line_c) / (double)line_b;

    int draw_x1 = center_x + (math_x1 * scale);
    int draw_y1 = center_y - (math_y1 * scale);
    int draw_x2 = center_x + (math_x2 * scale);
    int draw_y2 = center_y - (math_y2 * scale);

    canvas.DrawPointLine(draw_x1, draw_y1, draw_x2, draw_y2, Color::Blue);
  }
  // Jika garis lebih tegak / curam
  else {
    // Pakai jarak -20 sampai 20 biar keliatan panjang
    double math_y1 = -20.0;
    double math_x1 = -((line_b * math_y1) + line_c) / (double)line_a;

    double math_y2 = 20.0;
    double math_x2 = -((line_b * math_y2) + line_c) / (double)line_a;

    int draw_x1 = center_x + (math_x1 * scale);
    int draw_y1 = center_y - (math_y1 * scale);
    int draw_x2 = center_x + (math_x2 * scale);
    int draw_y2 = center_y - (math_y2 * scale);

    canvas.DrawPointLine(draw_x1, draw_y1, draw_x2, draw_y2, Color::Blue);
  }
}