#include <algorithm>
#include <iostream>
#include <optional>

template <int N = 4> class RB {
public:
  bool repeat() {
    unsigned long long mask = 0ull;
    for (int i = 0; i < size; i++) {
      unsigned long long thismask = 1ull << (buf[(N + pos - size + i) % N] - 'a');
      if ((thismask & mask) > 0) return true;
      mask |= thismask;
    }
    return false;
  }

  void add(char c) {
    buf[pos] = c;
    pos = (pos + 1) % N;
    size = std::min(size + 1, N);
  }

  void dump(std::ostream& out) {
    out << "RB<" << N << "> (" << size << "):";
    for (int i = 0; i < N; i++) {
      if (i == pos) {
        out << "^";
      }
      out << " " << std::hex << buf[i];
    }
    out << std::endl;
  }

private:
  char buf[N];
  int pos = 0;
  int size = 0;
};

int main(int argc, char **argv) {
  RB<4> rb;
  int i = 0;
  int skip = 3;
  for (; !std::cin.eof() && std::cin.peek() != '\n'; i++) {
    rb.add(std::cin.get());
    if (skip > 0) {
      skip--;
    } else if (!rb.repeat()) {
      rb.dump(std::cerr);
      std::cout << i + 1 << std::endl;
      break;
    }
  }

  return 0;
}
