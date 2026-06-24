#include "stack_module.h"
#include "ftxui/dom/elements.hpp"
#include "stack.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>
#include <sstream>

StackModule::StackModule() {
  using namespace ftxui;
  postfix = "";
  result_text = "Klik Play untuk menghitung";

  // Container input postfix
  auto input_postfix = Input(&postfix, "2 3 +");
  // Filter input
  input_postfix = CatchEvent(input_postfix, [&](Event event) {
    if (event.is_character()) {
      char c = event.character()[0];
      bool allowed = std::isdigit(c) || c == ' ' || c == '+' || c == '-' ||
                     c == '*' || c == '/';
      return !allowed;
    }
    return false;
  });

  auto label_postfix = Renderer([&] { return text("Postfix : "); });
  auto row_postfix = Container::Horizontal({label_postfix, input_postfix});

  // Tombol Play
  auto btn_play = Button("Play", [&] {
    try {
      result_text = CalculatePostfix(postfix);
    } catch (const std::exception &e) {
      result_text = std::string("Error: ") + e.what();
    }
  });

  // Gabungkan semua ke container vertikal
  this->container = Container::Vertical({row_postfix, btn_play});
}

std::string StackModule::CalculatePostfix(const std::string &expr) {
  Stack stack1;
  init(&stack1);

  std::stringstream ss(expr);
  std::string token;

  while (ss >> token) {
    if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
      push(&stack1, std::stoi(token));
    } else {
      int kanan = peek(&stack1);
      pop(&stack1);
      int kiri = peek(&stack1);
      pop(&stack1);

      if (token == "+")
        push(&stack1, kiri + kanan);
      else if (token == "-")
        push(&stack1, kiri - kanan);
      else if (token == "*")
        push(&stack1, kiri * kanan);
      else if (token == "/")
        push(&stack1, kiri / kanan);
    }
  }

  int hasil = peek(&stack1);
  // Bersihkan memori (opsional tapi baik)
  while (!isEmpty(&stack1))
    pop(&stack1);

  return "Hasil: " + std::to_string(hasil);
}

ftxui::Element StackModule::GetOutputElement() {
  using namespace ftxui;
  // Return teks hasil perhitungan
  return vbox({text("Output Log") | bold | color(Color::Cyan), separator(),
               text(result_text) | color(Color::Green)});
}

void StackModule::DrawCanvas(ftxui::Canvas &canvas) {
  using namespace ftxui;
  // Gambar stack secara visual
  canvas.DrawPointLine(0, 50, 100, 50, Color::GrayDark); // Sumbu X
  canvas.DrawPointLine(50, 0, 50, 100, Color::GrayDark); // Sumbu Y
}