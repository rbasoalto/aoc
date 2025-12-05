#include <sys/types.h>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::vector<std::pair<uint64_t, uint64_t>> ranges;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    uint64_t left, right;
    char dash;
    std::stringstream ss(line);
    ss >> left >> dash >> right;
    ranges.emplace_back(left, right);
  }

  auto second_order = [](const auto& a, const auto& b) {
    return a.second < b.second;
  };

  std::sort(ranges.begin(), ranges.end(), second_order);

  auto finder = [](const std::pair<uint64_t, uint64_t>& a, uint64_t b) {
    return a.second < b;
  };

  uint64_t n = 0;
  uint64_t c;
  while (std::cin >> c) {
    auto it = std::lower_bound(ranges.begin(), ranges.end(), c, finder);
    bool found = false;
    while (it != ranges.end()) {
      if (c >= it->first && c <= it->second) {
        found = true;
        break;
      }
      ++it;
    }
    if (found)
      ++n;
  }

  std::cout << n << std::endl;

  if (argc > 1) {
    delete input;
  }
}
