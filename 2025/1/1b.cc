#include <iostream>

int main(int argc, char *argv[]) {
  char c;
  int n;
  int pos = 50;
  int num_zeros = 0;
  while (std::cin >> c >> n) {
    int delta = n;
    if (c == 'L') {
      pos = (pos-100)%100;
      pos -= delta;

      num_zeros -= pos/100;

      pos %= 100;
      if (pos < 0)
          pos += 100;
    } else {
      pos += delta;
      num_zeros += pos / 100;
      pos %= 100;
    }
  }
  std::cout << num_zeros << std::endl;
  return 0;
}
