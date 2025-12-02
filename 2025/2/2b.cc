#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

bool is_silly_k(const std::vector<char> &digits, size_t k) {
  if (digits.size() % k != 0) {
    return false;
  }

  size_t pattern_size = digits.size() / k;
  for (size_t i = 0; i < pattern_size; i++) {
    char d = digits[i];
    for (size_t j = 1; j < k; j++) {
      if (digits[j * pattern_size + i] != d) {
        return false;
      }
    }
  }
  return true;
}

bool is_silly(uint64_t n) {
  std::vector<char> digits;
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  for (size_t k = 2; k <= digits.size(); k++) {
    if (is_silly_k(digits, k)) {
      return true;
    }
  }
  return false;
}

int main() {
  uint64_t sum = 0;
  std::string input;
  while (std::getline(std::cin, input, ',')) {
    if (input.empty())
      continue;
    std::stringstream ss(input);
    uint64_t from, to;
    char dash;
    ss >> from >> dash >> to;

    for (uint64_t i = from; i <= to; i++) {
      if (is_silly(i)) {
        sum += i;
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
