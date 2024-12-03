#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  std::vector<long long int> l, r;
  long long int lt, rt;
  while (std::cin >> lt >> rt) {
    l.push_back(lt);
    r.push_back(rt);
  }

  std::sort(l.begin(), l.end());
  std::sort(r.begin(), r.end());

  unsigned long long int d = 0;

  for(auto li = l.begin(), ri = r.begin();
      li != l.end() && ri != r.end();
      li++, ri++) {
    d += std::abs(*li - *ri);
  }

  std::cout << d << std::endl;

  return 0;
}
