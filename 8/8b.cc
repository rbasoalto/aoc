#include <array>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

int main(int argc, char** argv) {
  std::string line;
  long scores[100][100] = {};

  int vertical_pos[100][10];

  uint8_t map[100][100] = {};

  int row = 0;
  std::getline(std::cin, line);
  int W = line.size();

  for (int i = 0; i < W; i++) {
    for (int j = 0; j < 10; j++) {
      vertical_pos[i][j] = -1;
    }
  }

  while (true) {
    int left_pos[10] = {-1 , -1, -1, -1, -1, -1, -1, -1, -1, -1};

    for (int i = 0; i < W; i++) {
      int8_t cur = line[i]-'0';

      map[row][i] = cur;

      // left visibility
      int leftmost_visible = 0;
      for (int h = cur; h < 10; h++) {
        leftmost_visible = std::max(left_pos[h], leftmost_visible);
      }
      left_pos[cur] = i;
      // left score
      scores[row][i] = leftmost_visible >= 0 ? (i - leftmost_visible) : 0;

      // top visibility
      int topmost_visible = 0;
      for (int h = cur; h < 10; h++) {
        topmost_visible = std::max(vertical_pos[i][h], topmost_visible);
      }
      vertical_pos[i][cur] = row;
      // top score
      scores[row][i] *= topmost_visible >= 0 ? (row - topmost_visible) : 0;
    }

    row++;
    if (!std::getline(std::cin, line)) {
      break;
    }
  }

  for (int i = 0; i < W; i++) {
    for (int j = 0; j < 10; j++) {
      vertical_pos[i][j] = row;
    }
  }


  long best_score = 0;

  for (int rowi = row - 1; rowi >= 0; rowi--) {
    int right_pos[10] = {W , W, W, W, W, W, W, W, W, W};

    for (int coli = W - 1; coli >= 0; coli--) {
      int8_t cur = map[rowi][coli];

      // right visibility
      int rightmost_visible = W - 1;
      for (int h = cur; h < 10; h++) {
        rightmost_visible = std::min(right_pos[h], rightmost_visible);
      }
      right_pos[cur] = coli;
      // right score
      scores[rowi][coli] *= rightmost_visible < W ? (rightmost_visible - coli) : 0;

      // bottom visibility
      int bottommost_visible = row - 1;
      for (int h = cur; h < 10; h++) {
        bottommost_visible = std::min(vertical_pos[coli][h], bottommost_visible);
      }
      vertical_pos[coli][cur] = rowi;
      // bottom score
      scores[rowi][coli] *= bottommost_visible < row ? (bottommost_visible - rowi) : 0;

      best_score = std::max(scores[rowi][coli], best_score);
    }

  }

#ifdef DEBUG
  for (int rowi = 0; rowi < row; rowi++) {
    for (int coli = 0; coli < W; coli++) {
      std::cerr << std::setw(5) << scores[rowi][coli];
    }
    std::cerr << std::endl;
  }
#endif


  std::cout << best_score << std::endl;

  return 0;
}
