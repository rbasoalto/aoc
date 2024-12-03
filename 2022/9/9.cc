#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include <utility>

using XY = std::pair<int, int>;

template<>
struct std::hash<XY> {
  std::size_t operator()(const XY& xy) const noexcept {
    auto h1 = std::hash<int>{}(xy.first);
    auto h2 = std::hash<int>{}(xy.second);
    return h1 ^ (h2 << 1);
  }
};

int main(int argc, char** argv) {

  std::string dir;
  int count;

  std::unordered_set<XY> tail_pos;

  int x = 0, y = 0;
  int tx = 0, ty = 0;

  tail_pos.emplace(0, 0);

#ifdef DEBUG
  int minx = INT_MAX;
  int maxx = INT_MIN;
  int miny = INT_MAX;
  int maxy = INT_MIN;
#endif

  while (std::cin >> dir >> count) {
    while (count-- > 0) {
      switch (dir[0]) {
        case 'U':
          y++;
          if (y - ty > 1) {
            ty = y - 1;
            tx = x;
          }
        break;
        case 'D':
          y--;
          if (ty - y > 1) {
            ty = y + 1;
            tx = x;
          }
        break;
        case 'L':
          x--;
          if (tx - x > 1) {
            tx = x + 1;
            ty = y;
          }
        break;
        case 'R':
          x++;
          if (x - tx > 1) {
            tx = x - 1;
            ty = y;
          }
        break;
      }
      tail_pos.emplace(tx, ty);
    }


#ifdef DEBUG
    minx = std::min(minx, x);
    miny = std::min(miny, y);
    maxx = std::max(maxx, x);
    maxy = std::max(maxy, y);
#endif
  }

#ifdef DEBUG
  std::cerr << minx << " <= x <= " << maxx << std::endl;
  std::cerr << miny << " <= y <= " << maxy << std::endl;
#endif

  std::cout << tail_pos.size() << std::endl;

  return 0;
}
