#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  std::vector<long long int> l;
  std::unordered_map<long long int, unsigned long long int> r;
  long long int lt, rt;
  while (std::cin >> lt >> rt) {
    l.push_back(lt);
    auto it = r.find(rt);
    if (it != r.end()) {
      it->second++;
    } else {
      r[rt] = 1;
    }
  }

  unsigned long long int d = 0;

  for(auto li = l.begin(); li != l.end(); li++) {
    auto ri = r.find(*li);
    if (ri != r.end()) {
      d += (*li) * (ri->second);
    }
  }

  std::cout << d << std::endl;

  return 0;
}
