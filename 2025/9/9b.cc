#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#define ABS(x) (((x) > 0) ? (x) : (-(x)))

using point_t = std::pair<int64_t, int64_t>;

int64_t area(const point_t& a, const point_t& b) {
  return (ABS(a.first - b.first) + 1) * (ABS(a.second - b.second) + 1);
}

bool segments_cross(const point_t& s1a, const point_t& s1b, const point_t& s2a,
                    const point_t& s2b) {
  int64_t hx1, hx2, hy;
  int64_t vx, vy1, vy2;

  if (s1a.first == s1b.first) {
    // s1 is vertical
    if (s2a.first == s2b.first) {
      // s2 is also vertical: no cross
      return false;
    } else {
      vx = s1a.first;
      vy1 = s1a.second;
      vy2 = s1b.second;

      hx1 = s2a.first;
      hx2 = s2b.first;
      hy = s2a.second;
    }
  } else {
    // s1 is horizontal
    if (s2a.first == s2b.first) {
      // s2 is vertical
      vx = s2a.first;
      vy1 = s2a.second;
      vy2 = s2b.second;

      hx1 = s1a.first;
      hx2 = s1b.first;
      hy = s1a.second;
    } else {
      return false;
    }
  }

  bool crossx = std::min(hx1, hx2) < vx && std::max(hx1, hx2) > vx;
  bool crossy = std::min(vy1, vy2) < hy && std::max(vy1, vy2) > hy;
  if (crossx && crossy) {
    return true;
  }
  return false;
}

bool any_point_within_rect(const point_t& p1, const point_t& p2,
                           const std::vector<point_t>& poly) {
  int64_t minx = std::min(p1.first, p2.first);
  int64_t maxx = std::max(p1.first, p2.first);
  int64_t miny = std::min(p1.second, p2.second);
  int64_t maxy = std::max(p1.second, p2.second);
  for (const auto& p : poly) {
    if (minx < p.first && p.first < maxx && miny < p.second && p.second < maxy)
      return true;
  }
  return false;
}

// Might fail in some convex cases
bool rect_within_polygon(const point_t& p1, const point_t& p2,
                         const std::vector<point_t>& poly) {
  // rect corner points
  point_t r1{std::min(p1.first, p2.first), std::min(p1.second, p2.second)};
  point_t r2{std::min(p1.first, p2.first), std::max(p1.second, p2.second)};
  point_t r3{std::max(p1.first, p2.first), std::max(p1.second, p2.second)};
  point_t r4{std::max(p1.first, p2.first), std::min(p1.second, p2.second)};

  for (size_t i = 0; i < poly.size(); i++) {
    if (segments_cross(r1, r2, poly[i], poly[(i + 1) % poly.size()]) ||  //
        segments_cross(r2, r3, poly[i], poly[(i + 1) % poly.size()]) ||  //
        segments_cross(r3, r4, poly[i], poly[(i + 1) % poly.size()]) ||  //
        segments_cross(r4, r1, poly[i], poly[(i + 1) % poly.size()]))
      return false;
  }
  return true;
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

  std::string line;
  while (std::getline(*input, line)) {
    int64_t x, y;
    char c;

    *input >> x >> c >> y;

    points.emplace_back(x, y);

    std::cout << points.back() << std::endl;
  }

  int64_t max = 0;

  for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
    for (auto it2 = it1 + 1; it2 != points.end(); ++it2) {
      if (rect_within_polygon(*it1, *it2, points) &&
          !any_point_within_rect(*it1, *it2, points)) {
        int64_t a = area(*it1, *it2);
        if (a > max) {
          max = a;
          // std::cout << "max " << max << " at " << *it1 << *it2 << std::endl;
        }
      }
    }
  }

  std::cout << max << std::endl;

  if (argc > 1) {
    delete input;
  }
}
