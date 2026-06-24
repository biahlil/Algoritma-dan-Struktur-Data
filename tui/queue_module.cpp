#include "queue_module.h"
#include "ftxui/component/component_base.hpp"
#include "queue.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <sstream>

QueueModule::QueueModule() {
  using namespace ftxui;
  window = "3";
  elements = "1 2 3 4 5";
  result_text = "Klik Play untuk menghitung";

  // Container  input field
  auto input_window = Input(&window, "4");
  input_window = CatchEvent(input_window, [&](Event event) {
    if (event.is_character()) {
      char c = event.character()[0];
      return !std::isdigit(c); // Blokir semua kecuali angka
    }
    return false;
  });
  auto label_window = Renderer([&] { return text("Window (K): "); });
  auto row_window = Container::Horizontal({label_window, input_window});

  auto input_elements = Input(&elements, "2 3 4 5");
  input_elements = CatchEvent(input_elements, [&](Event event) {
    if (event.is_character()) {
      char c = event.character()[0];
      bool allowed = std::isdigit(c) || c == ' ' || c == '-';
      return !allowed;
    }
    return false;
  });
  auto label_elements = Renderer([&] { return text("Elements : "); });

  auto row_elements = Container::Horizontal({label_elements, input_elements});

  // Tombol Play
  auto btn_play = Button("Play", [&] {
    try {
      result_text = CalculateSlidingWindow(elements, window);
    } catch (const std::exception &e) {
      result_text = std::string("Error: ") + e.what();
    }
  });

  this->container = Container::Vertical({row_window, row_elements, btn_play});
}

std::string QueueModule::CalculateSlidingWindow(const std::string &elem_str,
                                                const std::string &k_str) {
  int k = std::stoi(k_str);

  // Parse elements string ke vector<int>
  std::vector<int> nums;
  std::stringstream ss(elem_str);
  int num;
  while (ss >> num) {
    nums.push_back(num);
  }

  int n = nums.size();
  if (k > n)
    return "Error: Window size lebih besar dari jumlah elemen!";

  Queue queue1;
  init(&queue1);

  std::string output = "";
  int window_sum = 0;

  // Fase 1: Isi window pertama
  for (int i = 0; i < k; i++) {
    enqueue(&queue1, nums[i]);
    window_sum += nums[i];
  }
  output += std::to_string(window_sum);

  // Fase 2: Sliding Window
  for (int i = k; i < n; i++) {
    int yang_dibuang = front(&queue1);
    dequeue(&queue1);

    window_sum = window_sum - yang_dibuang + nums[i];
    enqueue(&queue1, nums[i]);

    output += " " + std::to_string(window_sum);
  }

  return "Hasil: " + output;
}

ftxui::Element QueueModule::GetOutputElement() {
  using namespace ftxui;
  // Return teks hasil perhitungan
  return vbox({text("Output Log") | bold | color(Color::Cyan), separator(),
               text(result_text) | color(Color::Green)});
}

void QueueModule::DrawCanvas(ftxui::Canvas &canvas) {
  using namespace ftxui;
  // Gambar stack secara visual
  canvas.DrawPointLine(0, 50, 100, 50, Color::GrayDark); // Sumbu X
  canvas.DrawPointLine(50, 0, 50, 100, Color::GrayDark); // Sumbu Y
}