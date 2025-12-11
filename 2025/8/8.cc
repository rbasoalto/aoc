#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define NUM_PAIRS 1000ul
#define NUM_CIRCUITS_MUL 3ul

#define SQ(expr) (double(expr) * double(expr))

using t3d = std::tuple<int, int, int>;

double sqdist(const t3d& p1, const t3d& p2) {
  return SQ(std::get<0>(p1) - std::get<0>(p2)) +
         SQ(std::get<1>(p1) - std::get<1>(p2)) +
         SQ(std::get<2>(p1) - std::get<2>(p2));
}

std::ostream& operator<<(std::ostream& s, const t3d& point) {
  return s << "(" << std::get<0>(point)  //
           << "," << std::get<1>(point)  //
           << "," << std::get<2>(point) << ")";
}

template <class T>
std::ostream& operator<<(std::ostream& s, const std::unordered_set<T>& c) {
  for (const auto& x : c) {
    s << x << ",";
  }
  return s;
}

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::vector<t3d> coords;
  std::vector<std::vector<float>> distances;
  std::vector<std::pair<size_t, size_t>> pairs;

  std::string line;
  while (std::getline(*input, line)) {
    std::stringstream ss(line);
    char comma;
    int x, y, z;
    ss >> x >> comma >> y >> comma >> z;
    coords.emplace_back(x, y, z);
    auto& thiscoord = coords.back();
    distances.emplace_back();
    auto& thisdist = distances.back();
    for (size_t i = 0; i < coords.size() - 1; ++i) {
      pairs.emplace_back(i, coords.size() - 1);
      double d = sqdist(coords[i], thiscoord);
      distances[i].push_back(d);
      thisdist.push_back(d);
    }
    thisdist.push_back(0);
  }

  auto distance_heap_comparator = [&](const std::pair<size_t, size_t>& p1,
                                      const std::pair<size_t, size_t>& p2) {
    return distances[p1.first][p1.second] > distances[p2.first][p2.second];
  };

  std::make_heap(pairs.begin(), pairs.end(), distance_heap_comparator);

  std::unordered_map<size_t, std::unordered_set<size_t>*> circuits;
  std::unordered_set<std::unordered_set<size_t>*> all_circuits;

  for (size_t i = 0; i < NUM_PAIRS; i++) {
    std::pop_heap(pairs.begin(), pairs.end(), distance_heap_comparator);
    auto p = pairs.back();
    pairs.pop_back();

    // std::cout << "looking at pair " << p.first << coords[p.first] << ","
    //           << p.second << coords[p.second]
    //           << " which are at d2=" << distances[p.first][p.second]
    //           << std::endl;

    std::unordered_set<size_t>* circuit = nullptr;
    if (auto it = circuits.find(p.first); it != circuits.end()) {
      circuit = it->second;
      // std::cout << p.first << " already in circuit " << *circuit << std::endl;
    }
    if (auto it = circuits.find(p.second); it != circuits.end()) {
      auto existing_circuit = it->second;
      // std::cout << p.second << " already in circuit " << *existing_circuit
      //           << std::endl;
      if (circuit != nullptr && circuit != existing_circuit) {
        existing_circuit->merge(*circuit);
        // std::cout << "merging circuits! now " << *existing_circuit << std::endl;
        all_circuits.erase(circuit);
        delete circuit;
      }
      circuit = existing_circuit;
    }
    if (circuit == nullptr) {
      // std::cout << "new circuit!" << std::endl;
      circuit = new std::unordered_set<size_t>;
    }
    circuit->insert(p.first);
    circuit->insert(p.second);
    for (size_t j : *circuit) {
      circuits[j] = circuit;
    }
    // std::cout << "inserting circuit w size " << circuit->size() << ": "
    //           << *circuit << std::endl;
    all_circuits.insert(circuit);
  }

  // std::cout << "done connecting stuff" << std::endl;

  std::vector<size_t> sizes;
  sizes.reserve(all_circuits.size());
  for (const auto* c : all_circuits) {
    // std::cout << "circuit w size " << c->size() << ": " << *c << std::endl;
    sizes.push_back(c->size());
  }

  std::make_heap(sizes.begin(), sizes.end());

  size_t max_muls = std::min(sizes.size(), NUM_CIRCUITS_MUL);

  uint64_t sizemul = 1;
  for (int i = 0; i < max_muls; i++) {
    std::pop_heap(sizes.begin(), sizes.end());
    auto s = sizes.back();
    sizes.pop_back();
    // std::cout << "  multiplying size " << s << std::endl;
    sizemul *= s;
  }

  std::cout << sizemul << std::endl;

  if (argc > 1) {
    delete input;
  }
}
