#include <sys/types.h>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct SVHash {
  using is_transparent = void;

  size_t operator()(std::string_view sv) const {
    return std::hash<std::string_view>{}(sv);
  }
};

using svset = std::unordered_set<std::string_view, SVHash, std::equal_to<>>;

template <class T>
using svmap = std::unordered_map<std::string_view, T, SVHash, std::equal_to<>>;

template <class T>
using smap = std::unordered_map<std::string, T, SVHash, std::equal_to<>>;

using adjmap = smap<std::vector<std::string>>;

struct path_counts {
  uint64_t total;
  uint64_t via_fft;
  uint64_t via_dac;
  uint64_t via_fft_and_dac;

  path_counts operator+=(const path_counts& other) {
    total += other.total;
    via_fft += other.via_fft;
    via_dac += other.via_dac;
    via_fft_and_dac += other.via_fft_and_dac;
    return *this;
  }

  friend path_counts operator+(path_counts lhs, const path_counts& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend std::ostream& operator<<(std::ostream& os, const path_counts& counts) {
    return os << "{total:" << counts.total << ", fft:" << counts.via_fft
              << ", dac:" << counts.via_dac
              << ", fft+dac:" << counts.via_fft_and_dac << "}";
  }
};

path_counts count_paths(const adjmap& adj, std::string_view from,
                        std::string_view to, svmap<path_counts>* memo) {

  if (from == to) {
    return {1, 0, 0, 0};
  }

  if (auto m = memo->find(from); m != memo->end()) {
    return m->second;
  }

  path_counts paths = {0, 0, 0, 0};

  for (const auto& n : adj.find(from)->second) {
    paths += count_paths(adj, n, to, memo);
  }

  if (from == "fft") {
    paths.via_fft = paths.total;
    paths.via_fft_and_dac = paths.via_dac;
  }
  if (from == "dac") {
    paths.via_dac = paths.total;
    paths.via_fft_and_dac = paths.via_fft;
  }

  memo->emplace(from, paths);
  return paths;
}

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  adjmap adj;

  std::string line;
  while (std::getline(*input, line)) {
    std::stringstream ss(line);
    std::string from, to;
    ss >> from;
    from.pop_back();  // drop trailing :

    auto& list = adj[from];
    while (ss >> to) {
      list.push_back(to);
    }
  }

  svmap<path_counts> memo;
  std::cout << count_paths(adj, "svr", "out", &memo) << std::endl;

  if (argc > 1) {
    delete input;
  }
}
