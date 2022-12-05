#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string a, b;
  long score = 0;
  while (std::cin >> a >> b) {
    char c1 = a[0] - 'A';
    char c2 = b[0] - 'X';
    // win score
    score += c2 * 3;
    // figure out shape
    score += 1 + (c1 + 3 + c2 - 1) % 3;
  }
  std::cout << score << std::endl;
  return 0;
}
