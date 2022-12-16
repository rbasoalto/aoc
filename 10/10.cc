#include <iostream>
#include <string>
#include <string_view>
#include <charconv>
#include <iomanip>

class Observer {
 public:
  Observer() : sum_strength_(0) {}
  void Update(long long x, unsigned long long clock) {
    if (clock >= 20 && clock <= 220 && (clock - 20) % 40 == 0) {
      sum_strength_ += x * clock;
#ifndef DEBUG
      std::cerr << "clock=" << std::setw(5) << clock << " x=" << std::setw(5) << x << std::endl;
#endif
    }
#ifdef DEBUG
    std::cerr << "clock=" << std::setw(5) << clock << " x=" << std::setw(5) << x << std::endl;
#endif
  }

  long long SumStrength() {
    return sum_strength_;
  }

 private:
  long long sum_strength_;
};

class State {
 public:
  State(Observer* o) : o_(o) {}

  void Tick() {
    clock_++;
    o_->Update(x_, clock_);
  }

  void AddX(long long x) {
    x_ += x;
  }
 private:
  long long x_ = 1;
  unsigned long long clock_ = 0;
  Observer* o_;
};

void ProcessInstruction(std::string_view instruction, State* st) {

  switch (instruction[0]) {
    case 'n':  // noop
      st->Tick();
      break;
    case 'a':  // addx
      st->Tick();
      st->Tick();
      auto arg = instruction.substr(5);
      long long x;
      auto fcr = std::from_chars(arg.data(), arg.data() + arg.size(), x);
      st->AddX(x);
      break;
  }

}

int main(int argc, char** argv) {
  Observer o;
  State st(&o);

  std::string instruction;
  while (std::getline(std::cin, instruction)) {
    ProcessInstruction(instruction, &st);
  }
  // let's look at the last cycle maybe?
  //ProcessInstruction("noop", &st);

  std::cout << o.SumStrength() << std::endl;

  return 0;
}
