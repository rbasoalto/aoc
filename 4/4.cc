#include <iostream>
#include <string>
#include <regex>

int main(int argc, char** argv) {
  std::regex re("(\\d+)-(\\d+),(\\d+)-(\\d+)", std::regex_constants::ECMAScript | std::regex_constants::optimize);
  std::string s;
  int count = 0;
  while (std::cin >> s) {
    std::smatch m;
    std::regex_match(s, m, re);
    int a1 = std::stoi(m[1].str()),
        a2 = std::stoi(m[2].str()),
        b1 = std::stoi(m[3].str()),
        b2 = std::stoi(m[4].str());
    bool overlap = (a1 <= b1 && a2 >= b2 || b1 <= a1 && b2 >= a2);
    count += overlap ? 1 : 0;
  }
  std::cout << count << std::endl;
  return 0;
}
