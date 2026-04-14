#pragma once
#include "module.h"

class LineModule : public IProjectModule {
private:
  // karena ftxui pake int jadi lebih baik buat var baru dan isinya di sesuaikan
  // dengan value dari line.h
  int line_a = 1, line_b = 0, line_c = -3;
  int point_x = 5, point_y = 0;
  ftxui::Component container; // Menyimpan input container

public:
  LineModule(); // Constructor
  // interface dari module.h
  std::string GetName() const override {
    return "Struct and Pointer: Garis";
  } // Nama dari soal
  ftxui::Component GetInputComponent() override { return container; }
  ftxui::Element GetOutputElement() override;
  void DrawCanvas(ftxui::Canvas &canvas) override;
};