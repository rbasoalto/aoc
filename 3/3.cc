#include <iostream>
#include <string>

int bit(char c) {
  if (c >= 'a') return c - 'a' + 1;
  return c - 'A' + 27;
}

int main(int argc, char** argv) {
  std::string line;
  long sum = 0;
  while (std::getline(std::cin, line)) {
    unsigned long long mask = 0;
    int half = line.size() / 2;
    for (int i = 0; i < half; i++) {
      mask |= 1ull<<bit(line[i]);
    }
    for (int i = half; i < line.size(); i++) {
      int bitnum = bit(line[i]);
      if (mask & (1ull<<bitnum)) {
        sum += bitnum;
        break;
      }
    }
  }
  std::cout << sum << std::endl;
}
