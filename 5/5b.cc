#include <iostream>
#include <iomanip>
#include <deque>
#include <vector>
#include <algorithm>

void PrintStacks(const std::vector<std::deque<char>>& stacks) {
  for (int i = 0; i < stacks.size(); i++) {
    std::cerr << std::setw(4) << i+1;
    for (const auto& item : stacks[i]) {
      std::cerr << " " << item;
    }
    std::cerr << std::endl;
  }
}

int main(int argc, char** argv) {
  std::string line, trash;
  std::getline(std::cin, line);
  size_t n = (line.size()+1)/4;
  std::vector<std::deque<char>> stacks(n);
  while (!std::cin.eof()) {
    if (line[1] == '1') {
      // done with stacks
      std::getline(std::cin, line);
      break;
    }
    for (int i = 0; i < n; i++) {
      char c = line[4*i + 1];
      if (c != ' ') {
        stacks[i].push_front(c);
      }
    }
    std::getline(std::cin, line);
  }

  PrintStacks(stacks);

  int count, from, to;
  std::deque<char> temp;

  while (!std::cin.eof() && std::cin.peek() != '\n') {
    std::cin.ignore(5); // move 
    if (std::cin.eof()) break;
    std::cin >> count;
    std::cin.ignore(5); // from 
    std::cin >> from;
    std::cin.ignore(3); // to 
    std::cin >> to;
    std::cin.ignore(1000, '\n');
    const auto start = stacks[from-1].cend() - count;
    const auto end = stacks[from-1].cend();
    stacks[to-1].insert(stacks[to-1].end(), start, end);
    stacks[from-1].erase(start, end);
    std::cerr << "move " << count << " from " << from << " to " << to << std::endl;
    PrintStacks(stacks);
  }

  for (const auto& stack : stacks) {
    std::cout << stack.back();
  }
  std::cout << std::endl;

  return 0;
}
