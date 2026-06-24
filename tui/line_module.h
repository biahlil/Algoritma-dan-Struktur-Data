#pragma once
#include "module.h"

class LineModule : public IProjectModule {
private:
  int line_a = 1, line_b = 0, line_c = -3;
  int point_x = 5, point_y = 0;
  ftxui::Component container; // Menyimpan input container

public:
  LineModule();
  int GetMeetingNumber() const override { return 1; }
  std::string GetMeetingName() const override { return "Struct and Pointer"; }
  std::string GetName() const override { return "Garis"; }
  ftxui::Component GetInputComponent() override { return container; }
  ftxui::Element GetOutputElement() override;
  void DrawCanvas(ftxui::Canvas &canvas) override;
};