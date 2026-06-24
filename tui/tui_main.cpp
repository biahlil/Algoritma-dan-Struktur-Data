#include "ftxui/component/app.hpp"       // for App
#include "ftxui/component/component.hpp" // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/dom/elements.hpp"
#include "module.h"
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

int main() {
  using namespace ftxui;
  auto screen = App::Fullscreen();

  std::vector<MeetingGroup> groups = BuildMeetingGroups();

  // Siapkan Data untuk Dropdown Pertemuan
  std::vector<std::string> meeting_names;
  for (auto &g : groups) {
    meeting_names.push_back("Pertemuan " + std::to_string(g.meeting_number) +
                            " : " + g.meeting_name);
  }
  int selected_meeting = 0;

  // Buat pengaturan kustom untuk Dropdown
  DropdownOption drop_option;

  // Masukkan data list dan pointer pilihan ke dalam opsi radiobox-nya
  drop_option.radiobox.entries = &meeting_names;
  drop_option.radiobox.selected = &selected_meeting;

  // Modifikasi transform untuk menghilangkan Border
  // (Secara bawaan FTXUI me-return: vbox({checkbox, border(list)}) )
  drop_option.transform = [](bool open, Element checkbox, Element list) {
    if (open) {
      // Hilangkan border()
      return vbox({checkbox, ftxui::separator(), list});
    }
    return checkbox;
  };

  // Panggil Dropdown dengan parameter (drop_option)
  auto meeting_dropdown = Dropdown(drop_option);

  // Buat Komponen Dinamis menggunakan Loop
  Components meeting_containers;
  for (auto &group : groups) {
    auto radio = Radiobox(&group.question_names, &group.selected_question);
    auto input_tab =
        Container::Tab(group.input_components, &group.selected_question);

    auto radio_with_window = Renderer(radio, [radio] {
      return window(text(" Pilih Soal "), radio->Render());
    });

    meeting_containers.push_back(
        Container::Vertical({radio_with_window, input_tab}));
  }

  auto main_meeting_tab = Container::Tab(meeting_containers, &selected_meeting);

  // Layout Utama
  auto right_panel = Container::Vertical(
      {meeting_dropdown, main_meeting_tab,
       Button(
           "Exit", [&] { screen.Exit(); }, ButtonOption::Border()) |
           center});

  auto renderer = Renderer(right_panel, [&] {
    // Ambil modul yang sedang aktif
    auto &active_module =
        groups[selected_meeting]
            .modules[groups[selected_meeting].selected_question];

    // Minta modul aktif untuk menggambar kanvasnya
    auto c = Canvas(100, 100);
    active_module->DrawCanvas(c);
    std::string nama =
        groups[selected_meeting].meeting_name + ": " + active_module->GetName();
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
