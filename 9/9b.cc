#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_set>
#include <utility>

using XY = std::pair<int, int>;

template <>
struct std::hash<XY> {
  std::size_t operator()(const XY& xy) const noexcept {
    auto h1 = std::hash<int>{}(xy.first);
    auto h2 = std::hash<int>{}(xy.second);
    return h1 ^ (h2 << 1);
  }
};

void Draw(std::ostream& out, int* x, int* y, int n) {
  int minx = 0, maxx = 0, miny = 0, maxy = 0;

  for (int i = 0; i < n; i++) {
    minx = std::min(minx, x[i]);
    maxx = std::max(maxx, x[i]);
    miny = std::min(miny, y[i]);
    maxy = std::max(maxy, y[i]);
  }

  int xsize = maxx - minx + 1;
  int ysize = maxy - miny + 1;
  char map[ysize][xsize];
  memset(map, '.', ysize * xsize);
  map[-miny][-minx] = 's';

  for (int i = n-1; i >= 0; i--) {
    map[y[i]-miny][x[i]-minx] = i+'0';
  }

  for (int row = ysize - 1; row >= 0; row--) {
    out.write(map[row], xsize);
    out << std::endl;
  }

  // blank line
  out << std::endl;

}

void UpdateTailPos(int x, int y, int* tx, int* ty) {
  int dy = y - *ty;
  int dx = x - *tx;

  if (dy > 1 && dx > 1) {  // diag UR
    *ty = y - 1;
    *tx = x - 1;
  } else if (dy > 1 && -dx > 1) {  // diag UL
    *ty = y - 1;
    *tx = x + 1;
  } else if (-dy > 1 && dx > 1) {  // diag DR
    *ty = y + 1;
    *tx = x - 1;
  } else if (-dy > 1 && -dx > 1) {  // diag DL
    *ty = y + 1;
    *tx = x + 1;
  } else if (dy > 1) {  // U
    *ty = y - 1;
    *tx = x;
  } else if (-dy > 1) {  // D
    *ty = y + 1;
    *tx = x;
  } else if (dx > 1) {  // R
    *tx = x - 1;
    *ty = y;
  } else if (-dx > 1) {  // L
    *tx = x + 1;
    *ty = y;
  }
}

int main(int argc, char** argv) {
  std::string dir;
  int count;

  std::unordered_set<XY> tail_pos;

  int x[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int y[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  tail_pos.emplace(0, 0);

  while (std::cin >> dir >> count) {
#ifdef DEBUG
    std::cerr << "==========" << std::endl << dir << " " << count << std::endl;
#endif
    while (count-- > 0) {
      switch (dir[0]) {
        case 'U':
          y[0]++;
          break;
        case 'D':
          y[0]--;
          break;
        case 'L':
          x[0]--;
          break;
        case 'R':
          x[0]++;
          break;
      }
      for (int i = 1; i < 10; i++) {
        UpdateTailPos(x[i-1], y[i-1], &x[i], &y[i]);
      }
      tail_pos.emplace(x[9], y[9]);
#ifdef DEBUG
      Draw(std::cerr, x, y, 10);
#endif
    }
  }

  std::cout << tail_pos.size() << std::endl;

  return 0;
}
