#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

// Ini adalah antarmuka (interface) dasar
class IProjectModule {
public:
  virtual ~IProjectModule() = default;

  // Nama untuk ditampilkan di Radiobox
  virtual std::string GetName() const = 0;

  // Mengembalikan Container milik modul
  virtual ftxui::Component GetInputComponent() = 0;

  // Mengembalikan element DOM output milik modul
  virtual ftxui::Element GetOutputElement() = 0;

  // Fungsi untuk menggambar di kanvas utama
  virtual void DrawCanvas(ftxui::Canvas &canvas) = 0;
};