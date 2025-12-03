#include <algorithm>
#include <cstddef>
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
    uint64_t acc = 0;
    size_t start_i = 0;
    for (size_t d = 0; d < NUM_DIGITS; d++) {
      char best = 0;
      for (size_t i = start_i; i <= line.size() - (NUM_DIGITS - d); i++) {
        if (line[i] > best) {
          best = line[i];
          start_i = i + 1;
        }
      }
      acc = acc * 10 + best - '0';
    }
    sum += acc;
  }
  std::cout << sum << std::endl;
  if (argc > 1) {
    delete input;
  }
  return 0;
}
