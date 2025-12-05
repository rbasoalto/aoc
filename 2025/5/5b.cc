#include <sys/types.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

class range_map {
 public:
  range_map() {}

  void add(uint64_t left, uint64_t right) {
    auto it = this->map_.lower_bound(left);
    if (it == this->map_.end()) {
      // empty, or reached the end
      it = this->map_.emplace_hint(it, left, true);
      ++it;  // == end
    } else {
      if (it->first == left) {
        // same as new range starting point
        if (it->second) {
          // started a range, ignore
          ++it;
        } else {
          // ended a range, which no longer ends here
          it = this->map_.erase(it);
        }
      } else {
        // beyond new range starting point
        if (it->second) {
          // starts another range, we can start it early
          it = this->map_.emplace_hint(it, left, true);
          ++it;
        } else {
          // ends a range, so we're *inside* a range, nothing to do
        }
      }
    }

    // delete everything in between...
    auto it2 = this->map_.upper_bound(right);
    this->map_.erase(it, it2);

    if (it2 == this->map_.end()) {
      // we're at the end, finish the range
      this->map_.emplace_hint(it2, right, false);
    } else {
      if (it2->second) {
        // starts next range, finish current
        this->map_.emplace_hint(it2, right, false);
      } else {
        // ends a range, so we're *inside* a range, no need to finish
      }
    }
  }

  uint64_t range_sizes() const {
    uint64_t count = 0;
    uint64_t prev = 0;
    for (const auto& l : this->map_) {
      if (l.second) {
        prev = l.first;
      } else {
        count += l.first - prev;
      }
    }
    return count;
  }

  void debug_print() {
    for (const auto& l : this->map_) {
      if (l.second) {
        std::cout << "[" << l.first << ", ";
      } else {
        std::cout << l.first << ")" << std::endl;
      }
    }
  }

  std::map<uint64_t, bool> map_;
};

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  range_map m;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    uint64_t first, second;
    char dash;
    std::stringstream ss(line);
    ss >> first >> dash >> second;
    ++second;  // excl

    m.add(first, second);
  }

  m.debug_print();

  std::cout << m.range_sizes() << std::endl;

  if (argc > 1) {
    delete input;
  }
}
