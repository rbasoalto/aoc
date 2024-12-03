#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int main() {
  std::string line;
  unsigned long long int safecount = 0;

  while (std::getline(std::cin, line)) {
    std::stringstream ss(std::move(line));
    int dir = 0;
    long long int n1 = 0, n2 = 0;
    ss >> n1;
    bool safe = true;
    while (ss >> n2) {
      // direction
      if (dir == 0) {
        dir = n2 > n1 ? 1 : -1;
      } else {
        if ((n2 > n1) != (dir > 0)) {
          safe = false;
          break;
        }
      }
      // magnitude
      long long int diff = std::abs(n2 - n1);
      if (diff < 1 || diff > 3) {
        safe = false;
        break;
      }
      // next
      n1 = n2;
    }
    safecount += safe ? 1 : 0;
  }

  std::cout << safecount << std::endl;

  return 0;
}
