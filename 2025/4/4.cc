#include <fstream>
#include <iostream>

#define MAXX 150
#define MAXY 150
#define THRESHOLD (0x14)

int main(int argc, char **argv) {
  std::istream *input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  unsigned char n[MAXY][MAXX]{0};
  size_t total = 0;

  std::string line;
  int i, j, maxj;
  for (i = 0; std::cin >> line; i++) {
    maxj = line.size();
    for (j = 0; j < maxj; j++) {
      if (line[j] == '@') {
        n[i + 1][j + 1] |= 0x10;

        n[i][j]++;
        n[i][j + 1]++;
        n[i][j + 2]++;
        n[i + 1][j]++;
        n[i + 1][j + 2]++;
        n[i + 2][j]++;
        n[i + 2][j + 1]++;
        n[i + 2][j + 2]++;
      }
      if (i > 0 && j > 0 && (n[i][j] & 0x10) && n[i][j] < THRESHOLD) {
        total++;
      }
    }
    // last col
    if (i > 0 && (n[i][j] & 0x10) && n[i][j] < THRESHOLD) {
      total++;
    }
  }
  // last row
  for (j = 1; j < maxj; j++) {
    if ((n[i][j] & 0x10) && n[i][j] < THRESHOLD) {
      total++;
    }
  }
  // last row,col
  if ((n[i][j] & 0x10) && n[i][j] < THRESHOLD) {
    total++;
  }

  std::cout << total << std::endl;

  if (argc > 1) {
    delete input;
  }
}
