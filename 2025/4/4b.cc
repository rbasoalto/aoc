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
  int i, j, maxi, maxj;
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
    }
  }
  maxi = i;

  size_t removed = 0;
  do {
    removed = 0;

    for (int i = 0; i < maxi; i++) {
      for (int j = 0; j < maxj; j++) {

        if ((n[i + 1][j + 1] & 0x10) && n[i + 1][j + 1] < THRESHOLD) {
          n[i + 1][j + 1] &= 0x0f;
          removed++;

          n[i][j]--;
          n[i][j + 1]--;
          n[i][j + 2]--;
          n[i + 1][j]--;
          n[i + 1][j + 2]--;
          n[i + 2][j]--;
          n[i + 2][j + 1]--;
          n[i + 2][j + 2]--;
        }
      }
    }
    total += removed;
  } while (removed > 0);

  std::cout << total << std::endl;

  if (argc > 1) {
    delete input;
  }
}
