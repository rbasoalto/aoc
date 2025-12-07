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

  std::vector<size_t> beams(line.size(), 0);
  beams[start] = 1;

  while (std::getline(std::cin, line)) {
    for (size_t i = 0; i < beams.size(); i++) {
      if (line[i] == '^' && beams[i] > 0) {
        size_t prev_beams = beams[i];
        if (i > 0)
          beams[i - 1] += prev_beams;
        beams[i] = 0;
        if (i + 1 < beams.size())
          beams[i + 1] += prev_beams;
      }
    }
  }

  size_t count = 0;
  for (size_t x : beams) {
    count += x;
  }
  std::cout << count << std::endl;

  if (argc > 1) {
    delete input;
  }
}
