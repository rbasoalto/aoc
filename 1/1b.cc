#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string line;
  long max[3] = {0, 0, 0};
  int imin = 0;
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
    if (cur > max[imin]) {
      max[imin] = cur;
      for (int i = 0; i < 3; i++) {
        if (max[i] < max[imin]) {
          imin = i;
        }
      }
    }
  }
  std::cout << max[0]+max[1]+max[2] << std::endl;
  return 0;
}
