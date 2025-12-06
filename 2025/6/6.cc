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

  std::vector<uint64_t> add, mul;

  bool first = true;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (!starts_with_number(line)) {
      break;
    }
    std::stringstream ss(line);
    uint64_t x;
    if (first) {
      while (ss >> x) {
        add.push_back(x);
        mul.push_back(x);
      }
      first = false;
      continue;
    }
    auto iadd = add.begin(), imul = mul.begin();
    while (ss >> x) {
      (*iadd) += x;
      (*imul) *= x;
      ++iadd;
      ++imul;
    }
  }

  // already read ops into line
  uint64_t sum = 0;
  auto iadd = add.begin(), imul = mul.begin();
  std::stringstream ss(line);
  char op;
  while (ss >> std::ws >> op >> std::ws) {
    if (op == '+') {
      sum += *iadd++;
      imul++;
    } else {
      sum += *imul++;
      iadd++;
    }
  }

  std::cout << sum << std::endl;

  if (argc > 1) {
    delete input;
  }
}
