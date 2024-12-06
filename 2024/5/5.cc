#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

template <class Container>
void split(const std::string& in, char delim, Container* out) {
  std::istringstream ins(in);
  std::string token;
  while(std::getline(ins, token, delim)) {
    out->push_back(std::move(token));
    token.clear();
  }
}

template <>
void split(const std::string& in, char delim, std::pair<std::string, std::string>* out) {
  size_t split_point = in.find(delim);
  out->first = in.substr(0, split_point);
  out->second = in.substr(split_point + 1);
}

template <class T>
class Comp {
private:
  const std::unordered_map<T, std::unordered_set<T>>& rules_;
public:
  Comp(const std::unordered_map<T, std::unordered_set<T>>& rules) : rules_(rules) {}

  bool operator()(const T& a, const T& b) {
    return rules_.at(a).contains(b);
  }
};


int main() {
  std::unordered_map<std::string, std::unordered_set<std::string>> must_not_appear_before;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.size() == 0) break;
    std::pair<std::string, std::string> rule;
    split(line, '|', &rule);
    must_not_appear_before[rule.first].emplace(std::move(rule.second));
  }

  long long int ans = 0;
  while (std::getline(std::cin, line)) {
    if (line.size() == 0) break;
    std::vector<std::string> elements;
    split(line, ',', &elements);
    if (std::is_sorted(elements.begin(), elements.end(), Comp{must_not_appear_before})) {
      ans += std::stoll(elements[elements.size()/2]);
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
