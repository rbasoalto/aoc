#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#define NUM_DIGITS 12

int main(int argc, char **argv) {
  std::istream *input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }
  uint64_t sum = 0;
  std::string line;
  while (std::getline(*input, line)) {
    uint64_t m[line.size() + 1][NUM_DIGITS];
    m[line.size()][0] = 0;
    for (int i = line.size() - 1; i >= 0; i--) {
      uint64_t digit = line[i] - '0';
      m[i][0] = std::max(digit, m[i + 1][0]);
    }

    uint64_t mult = 10;
    for (size_t d = 1; d < NUM_DIGITS; d++, mult *= 10) {
      m[line.size() - d][d] = 0;
      for (int i = line.size() - d - 1; i >= 0; i--) {
        uint64_t mdigit = mult * (line[i] - '0');
        m[i][d] = std::max(mdigit + m[i + 1][d - 1], m[i + 1][d]);
      }
    }
    sum += m[0][NUM_DIGITS - 1];
  }
  std::cout << sum << std::endl;
  if (argc > 1) {
    delete input;
  }
  return 0;
}
