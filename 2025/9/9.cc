#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#define DELTA(x, y) (((x) > (y)) ? ((x) - (y)) : ((y) - (x)))

using point_t = std::pair<uint64_t, uint64_t>;

uint64_t area(const point_t& a, const point_t& b) {
  return (DELTA(a.first, b.first) + 1) * (DELTA(a.second, b.second) + 1);
}

std::ostream& operator<<(std::ostream& os, const point_t& p) {
  return os << "(" << p.first << "," << p.second << ")";
}

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::vector<point_t> points;

  uint64_t max = 0;
  std::string line;
  while (std::getline(*input, line)) {
    uint64_t x, y;
    char c;

    *input >> x >> c >> y;
    point_t p{x, y};

    for (const point_t& p1 : points) {
      auto a = area(p, p1);

      // std::cout << "area btw " << p << " and " << p1 << " = " << a << std::endl;

      max = std::max(max, a);
    }
    points.push_back(p);
  }

  std::cout << max << std::endl;

  if (argc > 1) {
    delete input;
  }
}
