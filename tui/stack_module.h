#pragma once
#include "module.h"
#include <string>

class StackModule : public IProjectModule {
private:
  // Var Input
  std::string postfix;
  std::string result_text;
  ftxui::Component container;

public:
  StackModule();
  int GetMeetingNumber() const override { return 2; }
  std::string GetMeetingName() const override { return "Stack and Queue"; }
  std::string GetName() const override { return "Postfix Stack"; }
  ftxui::Component GetInputComponent() override { return container; }
  ftxui::Element GetOutputElement() override;
  void DrawCanvas(ftxui::Canvas &canvas) override;
  std::string CalculatePostfix(const std::string &expr);
};