#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

int main(int argc, char** argv) {
  std::string line;
  int8_t top[100];
  int bottom_pos[100][10];
  for (int i = 0; i < 100; i++) {
    top[i] = -1;
    for (int j = 0; j < 10; j++) {
      bottom_pos[i][j] = -1;
    }
  }
  std::bitset<100> map[100];
  int row = 0;
  std::getline(std::cin, line);
  int W = line.size();

  while (true) {
    int8_t left = -1;
    uint16_t right = 0u;
    int right_pos[10] = {-1 , -1, -1, -1, -1, -1, -1, -1, -1, -1};
    for (int i = 0; i < W; i++) {
      int8_t cur = line[i]-'0';
      // left
      if (cur > left) {
        std::cerr << row << ',' << i << " (" << (int)cur << ") visible from left" << std::endl;
        left = cur;
        map[row].set(i);
      }
      // top
      if (cur > top[i]) {
        std::cerr << row << ',' << i << " (" << (int)cur << ") visible from top" << std::endl;
        top[i] = cur;
        map[row].set(i);
      }
      // rightmost pos by height
      right_pos[cur] = i;
      // bottommost pos by height
      bottom_pos[i][cur] = row;
    }
    // mark right-visible trees
    int rightmost_visible = -1;
    for (int i = 9; i >= 0; i--) {
      int pos = right_pos[i];
      if (pos > rightmost_visible) {
        rightmost_visible = pos;
        std::cerr << row << ',' << pos << " (" << i << ") visible from right" << std::endl;
        map[row].set(pos);
      }
    }
    row++;
    if (!std::getline(std::cin, line)) {
      break;
    }
  }
  // mark bottom-visible trees
  for (int col = 0; col < W; col++) {
    int bottommost_visible = -1;
    for (int i = 9; i >= 0; i--) {
      int pos = bottom_pos[col][i];
      if (pos > bottommost_visible) {
        bottommost_visible = pos;
        std::cerr << pos << ',' << col << " (" << i << ") visible from bottom" << std::endl;
        map[pos].set(col);
      }
    }
  }

  uint32_t count = 0;
  for (int i = 0; i < row; i++) {
    count += map[i].count();
    std::cerr << map[i] << std::endl;
  }
  std::cout << count << std::endl;
  return 0;
}
