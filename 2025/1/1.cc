#include <iostream>

int main(int argc, char *argv[]) {
  char c;
  int n;
  int pos = 50;
  int num_zeros = 0;
  while (std::cin >> c >> n) {
    int delta = n;
    if (c == 'L') {
      pos += ((delta / 100) + 1) * 100;
      pos -= delta;
    } else {
      pos += delta;
    }
    pos = pos % 100;
    if (pos == 0)
      num_zeros++;
  }
  std::cout << num_zeros << std::endl;
  return 0;
}
