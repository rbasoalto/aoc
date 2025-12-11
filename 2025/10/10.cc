#include <bitset>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define MAX_SIZE 15

using bits = std::bitset<MAX_SIZE>;

void bt(const bits& desired, const std::vector<bits>& buttons, size_t i,
        bits* state, bits* pushed_buttons, bits* min_pushed_buttons) {
  if (i == buttons.size()) {
    bits test(desired);
    test ^= *state;

    if (!test.any() && pushed_buttons->count() < min_pushed_buttons->count()) {
      // std::cout << "new min " << *pushed_buttons << " < "
      //           << *min_pushed_buttons << std::endl;
      *min_pushed_buttons = *pushed_buttons;
    }
    return;
  }

  bt(desired, buttons, i + 1, state, pushed_buttons, min_pushed_buttons);

  *state ^= buttons[i];
  pushed_buttons->set(i);
  bt(desired, buttons, i + 1, state, pushed_buttons, min_pushed_buttons);
  *state ^= buttons[i];
  pushed_buttons->reset(i);
}

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  uint64_t pushes = 0;

  std::string line;
  while (std::getline(*input, line)) {
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, token, ' ');
    bits desired;
    for (size_t i = 1; i < token.size() - 1; ++i) {
      desired[i - 1] = token[i] == '#';
    }

    std::vector<bits> buttons;

    while (std::getline(ss, token, ' ')) {
      if (token[0] == '{')
        break;
      bits thisbutton;
      std::stringstream ss1(token);
      size_t button;
      char c;
      while (ss1 >> c >> button) {
        thisbutton.flip(button);
      }
      buttons.push_back(std::move(thisbutton));
    }

    // std::cout << "desired: " << desired << ", buttons: ";
    // for (const auto& button : buttons) {
    //   std::cout << button << ", ";
    // }
    // std::cout << std::endl;

    bits state;
    bits pushed_buttons;
    bits min_pushed_buttons;
    min_pushed_buttons.set();
    bt(desired, buttons, 0, &state, &pushed_buttons, &min_pushed_buttons);
    // std::cout << min_pushed_buttons << std::endl;

    pushes += min_pushed_buttons.count();
  }

  std::cout << pushes << std::endl;

  if (argc > 1) {
    delete input;
  }
}
