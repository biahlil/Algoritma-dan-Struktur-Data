#pragma once
#include "module.h"

class CircleModule : public IProjectModule {
private:
  int radius = 5;
  int point_x = 0, point_y = 0;
  int user_x = 3, user_y = 4;
  ftxui::Component container;

public:
  CircleModule();
  std::string GetName() const override {
    return "Struct and Pointer: Lingkaran";
  }
  ftxui::Component GetInputComponent() override { return container; }
  ftxui::Element GetOutputElement() override;
  void DrawCanvas(ftxui::Canvas &canvas) override;
};