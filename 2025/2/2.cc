#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

bool is_silly(uint64_t n) {
  std::vector<char> digits;
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  if (digits.size() % 2 != 0) {
    return false;
  }

  for (size_t i = 0; i < digits.size() / 2; i++) {
    if (digits[i] != digits[digits.size() / 2 + i]) {
      return false;
    }
  }
  return true;
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
