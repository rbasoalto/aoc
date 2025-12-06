#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool starts_with_number(const std::string& line) {
  for (char c : line) {
    if (c == ' ' || c == '\t') {
      continue;
    } else if (c >= '0' && c <= '9') {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::vector<uint64_t> nums;
  std::vector<bool> isnum;

  bool first = true;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (!starts_with_number(line)) {
      break;
    }
    if (first) {
      for (char c : line) {
        if (c == ' ') {
          isnum.push_back(false);
          nums.push_back(0);
        } else {
          isnum.push_back(true);
          nums.push_back(c - '0');
        }
      }
      first = false;
      continue;
    }

    auto numit = nums.begin();
    auto isnumit = isnum.begin();
    for (char c : line) {
      if (c != ' ') {
        (*numit) = (*numit) * 10 + (c - '0');
        *isnumit = true;
      }
      ++numit;
      ++isnumit;
    }
  }

  for (size_t i = 0; i < nums.size(); i++) {
    std::cout << (isnum[i] ? "N " : "  ") << nums[i] << std::endl;
  }

  // already read ops into line
  uint64_t sum = 0;
  std::stringstream ss(line);
  auto numit = nums.begin();
  auto isnumit = isnum.begin();
  char op;
  while (ss >> std::ws >> op >> std::ws) {
    uint64_t thisop;
    if (op == '+') {
      std::cout << "+" << std::endl;
      thisop = 0;
      while (*isnumit) {
        std::cout << *numit << std::endl;
        thisop += *numit++;
        isnumit++;
      }
    } else {
      std::cout << "*" << std::endl;
      thisop = 1;
      while (*isnumit) {
        std::cout << *numit << std::endl;
        thisop *= *numit++;
        isnumit++;
      }
    }
    std::cout << "=" << thisop << std::endl;
    sum += thisop;
    ++isnumit;
    ++numit;
  }

  std::cout << sum << std::endl;

  if (argc > 1) {
    delete input;
  }
}
