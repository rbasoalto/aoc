#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

int main() {
  uint64_t sum = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    unsigned int max = 0;
    for (auto it1 = line.begin(); it1 != line.end(); it1++) {
      for (auto it2 = it1 + 1; it2 != line.end(); it2++) {
        unsigned int candidate = 10 * (*it1 - '0') + (*it2 - '0');
        max = std::max(max, candidate);
      }
    }
    sum += max;
  }
  std::cout << sum << std::endl;
  return 0;
}
