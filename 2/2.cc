#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string a, b;
  long score = 0;
  while (std::cin >> a >> b) {
    char c1 = a[0] - 'A';
    char c2 = b[0] - 'X';
    // Shape score
    score += c2 + 1;
    switch (c2 - c1) {
      case 0: // draw
        score += 3;
        break;
      case 1:
      case -2: // win
        score += 6;
    }
  }
  std::cout << score << std::endl;
  return 0;
}
