#include <iostream>

enum State {
  INIT = 0,
  M = 1,
  U = 2,
  L = 3,
  OPEN = 4,
  FIRST = 5,
  COMMA = 6,
  SECOND = 7,
};

int main() {
  enum State state = INIT;

  char c = 0;
  long long int n1, n2;
  long long int result = 0;

  while (std::cin.get(c)) {

    switch (state) {
      case INIT:
        if (c == 'm')
          state = M;
        break;
      case M:
        if (c == 'u')
          state = U;
        else
          state = INIT;
        break;
      case U:
        if (c == 'l')
          state = L;
        else
          state = INIT;
        break;
      case L:
        if (c == '(')
          state = OPEN;
        else
          state = INIT;
        break;
      case OPEN:
        if (c >= '0' && c <= '9') {
          n1 = c - '0';
          state = FIRST;
        } else
          state = INIT;
        break;
      case FIRST:
        if (c == ',')
          state = COMMA;
        else if (c >= '0' && c <= '9') {
          n1 *= 10;
          n1 += c - '0';
        } else
          state = INIT;
        break;
      case COMMA:
        if (c >= '0' && c <= '9') {
          n2 = c - '0';
          state = SECOND;
        } else
          state = INIT;
        break;
      case SECOND:
        if (c == ')') {
          result += n1 * n2;
          state = INIT;
        } else if (c >= '0' && c <= '9') {
          n2 *= 10;
          n2 += c - '0';
        } else
          state = INIT;
        break;
    }
  }
  std::cout << result << std::endl;

  return 0;
}
