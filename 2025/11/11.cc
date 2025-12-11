#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::unordered_map<std::string, std::vector<std::string>> adj;

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

  std::unordered_map<std::string, uint64_t> path_counts;
  std::string node = "you";
  std::deque<std::string> q;
  q.emplace_back(std::move(node));
  while (!q.empty()) {
    node = std::move(q.front());
    q.pop_front();
    path_counts[node]++;
    for (const auto& n : adj[node]) {
      q.push_back(n);
    }
  }

  std::cout << path_counts["out"] << std::endl;

  if (argc > 1) {
    delete input;
  }
}
