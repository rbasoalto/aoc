#include <bit>
#include <iostream>
#include <string>

int bit(char c) {
  if (c >= 'a') return c - 'a' + 1;
  return c - 'A' + 27;
}

bool readline(std::istream& in, std::string& out) {
  return !std::getline(in, out).eof();
}

unsigned long long getmask(std::string_view str) {
  unsigned long long mask = 0;
  for (int i = 0; i < str.size(); i++) {
    mask |= 1ull<<bit(str[i]);
  }
  return mask;
}

int main(int argc, char** argv) {
  std::string line1, line2, line3;
  long sum = 0;
  while (readline(std::cin, line1) && readline(std::cin, line2) && readline(std::cin, line3)) {
    unsigned long long mask1 = getmask(line1), mask2 = getmask(line2), mask3 = getmask(line3);
    unsigned long long w = std::bit_width(mask1 & mask2 & mask3);
    sum += w - 1;
  }
  std::cout << sum << std::endl;
}
