#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> lines;
  std::vector<std::string> cols;

  unsigned long long int count = 0;

  while (std::cin >> lines.emplace_back()) {
    const std::string& line = lines.back();

    if (cols.empty()) {
      cols.resize(line.size());
    }

    auto cit = cols.begin();

    for (const auto& c : line) {
      cit++->push_back(c);
    }

    size_t pos = 0;

    while ((pos = line.find("XMAS", pos)) != std::string::npos) pos++, count++;

    pos = 0;

    while ((pos = line.find("SAMX", pos)) != std::string::npos) pos++, count++;
  }

  for (const auto& col : cols) {
    size_t pos = 0;

    while ((pos = col.find("XMAS", pos)) != std::string::npos) pos++, count++;

    pos = 0;

    while ((pos = col.find("SAMX", pos)) != std::string::npos) pos++, count++;
  }

  for (size_t i = 0; i < lines.size(); i++) for (size_t j = 0; j < cols.size(); j++) {
    if (i < lines.size() - 3 && j < cols.size() - 3) {
      if (lines[i][j] == 'X' && lines[i+1][j+1] == 'M' && lines[i+2][j+2] == 'A' && lines[i+3][j+3] == 'S') count++;
    }
    if (i < lines.size() - 3 && j >= 3) {
      if (lines[i][j] == 'X' && lines[i+1][j-1] == 'M' && lines[i+2][j-2] == 'A' && lines[i+3][j-3] == 'S') count++;
    }
    if (i >= 3 && j < cols.size() - 3) {
      if (lines[i][j] == 'X' && lines[i-1][j+1] == 'M' && lines[i-2][j+2] == 'A' && lines[i-3][j+3] == 'S') count++;
    }
    if (i >= 3 && j >= 3) {
      if (lines[i][j] == 'X' && lines[i-1][j-1] == 'M' && lines[i-2][j-2] == 'A' && lines[i-3][j-3] == 'S') count++;
    }
  }

  std::cout << count << std::endl;




  return 0;
}
