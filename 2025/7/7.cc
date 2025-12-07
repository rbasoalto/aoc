#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  std::string line;
  std::getline(std::cin, line);
  size_t start = line.find_first_of('S');

  std::vector<bool> beams(line.size(), false);
  beams[start] = true;

  size_t nsplits = 0;

  while (std::getline(std::cin, line)) {
    for (size_t i = 0; i < beams.size(); i++) {
      if (line[i] == '^' && beams[i]) {
        ++nsplits;
        if (i > 0)
          beams[i - 1] = true;
        beams[i] = false;
        if (i + 1 < beams.size())
          beams[i + 1] = true;
      }
    }
  }

  std::cout << nsplits << std::endl;

  if (argc > 1) {
    delete input;
  }
}
