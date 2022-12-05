#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string line;
  long max = 0;
  while (true) {
    long cur = 0;
    while (std::getline(std::cin, line)) {
      if (line.empty()) {
        break;
      }
      cur += std::stol(line);
    }
    if (cur == 0) {
      break;
    }
    if (cur > max) {
      max = cur;
    }
  }
  std::cout << max << std::endl;
  return 0;
}
