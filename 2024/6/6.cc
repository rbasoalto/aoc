#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::vector<bool>> map;

  size_t x=0, y=0;
  std::string line;
  while (std::getline(std::cin, line)) {
    auto& mapline = map.emplace_back();
    for (auto c : line) {
      if (c == '#') {
        mapline.push_back(true);
      } else {
        mapline.push_back(false);
        if (c == '^') {
          x = map.size() - 1;
          y = mapline.size() - 1;
        }
      }
    }
  }

  size_t X = map.size();
  size_t Y = map.back().size();

  std::vector<std::vector<bool>> visited(X, std::vector<bool>(Y));

  int dx = -1, dy = 0;
  while (x >= 0 && x < X && y >= 0 && y < Y) {
    visited[x][y] = true;

    if (x+dx >= 0 && x+dx < X && y+dy >= 0 && y+dy < Y) {
      if (map[x+dx][y+dy]) {
        if (dx == -1) {
          dx = 0;
          dy = 1;
        } else if (dx == 1) {
          dx = 0;
          dy = -1;
        } else if (dy == -1) {
          dx = -1;
          dy = 0;
        } else {
          dx = 1;
          dy = 0;
        }
      }
      x += dx;
      y += dy;
    } else {
      break;
    }
  }

  size_t count = 0;

  for (const auto& visitedline : visited) {
    for (const auto& bit : visitedline) {
      count += bit ? 1 : 0;
    }
  }

  std::cout << count << std::endl;

  return 0;
}
