#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  std::istream* input = &std::cin;
  if (argc > 1) {
    input = new std::fstream(argv[1]);
  }

  // do stuff

  if (argc > 1) {
    delete input;
  }
}
