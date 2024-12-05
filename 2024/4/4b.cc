#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> lines;

  unsigned long long int count = 0;

  while (std::cin >> lines.emplace_back());
  if (lines.back().size() == 0) lines.pop_back();

  size_t width = lines.back().size();


  for (size_t i = 1; i < lines.size() - 1; i++) for (size_t j = 1; j < width - 1; j++) {
    if (lines[i][j] != 'A') continue;

    if ((lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S' ||
         lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M') &&
        (lines[i-1][j+1] == 'M' && lines[i+1][j-1] == 'S' ||
         lines[i-1][j+1] == 'S' && lines[i+1][j-1] == 'M')) count++;
  }

  std::cout << count << std::endl;

  return 0;
}
