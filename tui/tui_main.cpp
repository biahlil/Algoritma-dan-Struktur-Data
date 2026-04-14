#include "circle_module.h"
#include "ftxui/component/app.hpp"       // for App
#include "ftxui/component/component.hpp" // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/dom/elements.hpp"
#include "line_module.h"
#include "module.h"
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

int main() {
  using namespace ftxui;
  auto screen = App::Fullscreen();

  // Daftarkan semua modul
  std::vector<std::shared_ptr<IProjectModule>> modules;
  modules.push_back(std::make_shared<LineModule>());
  modules.push_back(std::make_shared<CircleModule>());

  // Siapkan Tab dan Radiobox otomatis
  int current_mode = 0;
  std::vector<std::string> mode_entries;
  Components tab_components;

  for (auto &m : modules) {
    mode_entries.push_back(m->GetName());
    tab_components.push_back(m->GetInputComponent());
  }

  auto mode_selector = Radiobox(&mode_entries, &current_mode);
  auto tab_input = Container::Tab(tab_components, &current_mode);

  // Layout Utama
  auto right_panel = Container::Vertical(
      {mode_selector, tab_input,
       Button(
           "Exit", [&] { screen.Exit(); }, ButtonOption::Border()) |
           center});

  auto renderer = Renderer(right_panel, [&] {
    // Ambil modul yang sedang aktif
    auto &active_module = modules[current_mode];

    // Minta modul aktif untuk menggambar kanvasnya
    auto c = Canvas(100, 100);
    active_module->DrawCanvas(c);
    std::string nama = active_module->GetName();
    // Bangun jendela-jendela
    auto canvas_area = window(text(" Canvas / Visualization "),
                              canvas(std::move(c)) | center | flex) |
                       flex;
    auto input_area =
        window(text(" Interaction Input "), right_panel->Render()) | flex;

    // Minta modul aktif untuk memberikan teks outputnya
    auto output_area =
        window(text(" Output Log "), active_module->GetOutputElement()) | flex;

    return vbox({text(nama) | color(Color::Cyan) | bold | center, separator(),
                 hbox({canvas_area, vbox({input_area, output_area}) |
                                        size(WIDTH, LESS_THAN, 40)}) |
                     flex}) |
           border;
  });

  screen.Loop(renderer);
}
