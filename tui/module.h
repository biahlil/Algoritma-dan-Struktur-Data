#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

// Ini adalah antarmuka (interface) dasar
class IProjectModule {
public:
  virtual ~IProjectModule() = default;

  // Metadata
  virtual int GetMeetingNumber() const = 0;
  virtual std::string GetMeetingName() const = 0;

  // Nama untuk ditampilkan di Radiobox
  virtual std::string GetName() const = 0;

  // Mengembalikan Container milik modul
  virtual ftxui::Component GetInputComponent() = 0;

  // Mengembalikan element DOM output milik modul
  virtual ftxui::Element GetOutputElement() = 0;

  // Fungsi untuk menggambar di kanvas utama
  virtual void DrawCanvas(ftxui::Canvas &canvas) = 0;
};

// Struct untuk State UI
struct MeetingGroup {
  int meeting_number;
  std::string meeting_name;
  std::vector<std::string> question_names;
  std::vector<std::shared_ptr<IProjectModule>> modules;
  ftxui::Components input_components;

  int selected_question = 0; // State untuk Radiobox
};

// Fungsi Helper untuk merakit semua modul
std::vector<MeetingGroup> BuildMeetingGroups();
