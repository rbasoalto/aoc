#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int main() {
  std::string line;
  unsigned long long int safecount = 0;

  while (std::getline(std::cin, line)) {
    std::stringstream ss(std::move(line));
    std::vector<long long int> v;
    while (ss >> v.emplace_back());
    v.pop_back();
    std::cerr << "line " << v.size();

    for (auto excl = v.begin(); excl != v.end(); excl++) {
      std::cerr << ".";
      int dir = 0;
      long long int n1 = 0, n2 = 0;
      bool safe = true;
      auto it = v.begin();
      if (it == excl) it++;
      n1 = *it++;
      while (it != v.end()) {
        if (it == excl) {
          it++;
          continue;
        }
        n2 = *it++;
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
      if (safe) {
        std::cerr << " safe";
        safecount++;
        break;
      }
    }
    std::cerr << std::endl;
  }

  std::cout << safecount << std::endl;

  return 0;
}
