#pragma once
#include "module.h"
#include <string>

class QueueModule : public IProjectModule {
private:
  // Var Input
  std::string window;
  std::string elements;
  std::string result_text;
  ftxui::Component container; // Menyimpan input container

public:
  QueueModule();
  int GetMeetingNumber() const override { return 2; }
  std::string GetMeetingName() const override { return "Stack and Queue"; }
  std::string GetName() const override { return "Sliding Window Queue"; }
  ftxui::Component GetInputComponent() override { return container; }
  ftxui::Element GetOutputElement() override;
  void DrawCanvas(ftxui::Canvas &canvas) override;
  std::string CalculateSlidingWindow(const std::string &elem_str,
                                     const std::string &k_str);
};