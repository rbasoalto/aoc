#include <deque>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::ostream& Indent(std::ostream& out, int indent) {
  for (int i = 0; i < indent; i++) {
    out << "  ";
  }
  return out;
}

class Dir {
 public:
  Dir() : Dir("") {}
  Dir(std::string_view name) : name_(name) {}

  std::optional<Dir*> FindDir(std::string_view name) {
    for (auto& dir : dirs_) {
      if (dir.name_ == name) {
        return &dir;
      }
    }
    return std::nullopt;
  }

  Dir* AddDir(std::string_view name) {
    return &dirs_.emplace_back(name);
  }

  bool HasFile(std::string_view name) {
    for (const auto& pair : files_) {
      if (pair.first == name) {
        return true;
      }
    }
    return false;
  }

  void AddFile(std::string_view name, size_t size) {
    files_.emplace_back(name, size);
  }

  void DumpInternal(std::ostream& out, int indent) const {
    Indent(out, indent) << name_ << " (dir)" << std::endl;
    for (const auto& dir : dirs_) {
      dir.DumpInternal(out, indent+1);
    }
    for (const auto& file : files_) {
      Indent(out, indent+1) << file.first << " (" << file.second << ")" << std::endl;
    }
  }

  void ComputeSizes(std::function<bool(Dir*)> filter, std::vector<Dir*>* out) {
    size_t size = 0;
    for (auto& dir : dirs_) {
      dir.ComputeSizes(filter, out);
      size += *dir.size_;
    }
    for (const auto& file : files_) {
      size += file.second;
    }
    size_ = size;
    if (filter(this)) {
      out->push_back(this);
    }
  }

  std::string name_;
  std::vector<Dir> dirs_;
  std::vector<std::pair<std::string, size_t>> files_;
  std::optional<size_t> size_;
};

class Shell {
 public:
  Shell() { dir_stack_.push_back(&root_); }

  void ProcessCommand(std::string_view cmd, std::istream &in) {
    switch (cmd[2]) {
      case 'c':
        ProcessCd(cmd);
        break;
      case 'l':
        ProcessLs(in);
    }
  }

  void Dump(std::ostream &out) {
    out << "Dir stack: ";
    for (const auto dir : dir_stack_) {
      out << '/' << dir->name_;
    }
    out << std::endl;
    root_.DumpInternal(out, 0);
  }

  void ComputeSizes(std::function<bool(Dir*)> filter, std::vector<Dir*>* out) {
    root_.ComputeSizes(filter, out);
  }

 private:
  void ProcessCd(std::string_view cmd) {
    switch (cmd[5]) {
      case '/':
        dir_stack_.clear();
        dir_stack_.push_back(&root_);
        break;
      case '.':
        dir_stack_.pop_back();
        break;
      default:
        auto* current_dir = dir_stack_.back();
        auto dir = std::string_view{cmd}.substr(5);
        if (auto existing_dir = current_dir->FindDir(dir)) {
          dir_stack_.push_back(*existing_dir);
        } else {
          dir_stack_.push_back(current_dir->AddDir(dir));
        }
    }
  }

  void ProcessLs(std::istream &in) {
    auto* current_dir = dir_stack_.back();
    while (true) {
      if (in.peek() == '$' || in.eof()) {
        return;
      }
      std::string line;
      std::getline(in, line);
      if (line.starts_with("dir ")) {
        auto dirname = std::string_view{line}.substr(4);
        if (!current_dir->FindDir(dirname)) {
          current_dir->AddDir(dirname);
        }
      } else {
        size_t len = 0;
        long size = std::stol(line, &len);
        auto name = std::string_view(line).substr(len+1);
        if (!current_dir->HasFile(name)) {
          current_dir->AddFile(name, size);
        }
      }
    }
  }

  std::deque<Dir*> dir_stack_;
  Dir root_;
};

int main(int argc, char** argv) {
  Shell sh;
  std::string cmd;
  while (std::getline(std::cin, cmd)) {
    sh.ProcessCommand(cmd, std::cin);
    // std::cerr << "Processed " << cmd << std::endl;
    // sh.Dump(std::cerr);
  }

  std::vector<Dir*> interesting_dirs;
  sh.ComputeSizes([](Dir* d) -> bool {return *d->size_ <= 100000ull;}, &interesting_dirs);

  size_t sum_sizes = 0;
  for (auto* dir : interesting_dirs) {
    sum_sizes += *dir->size_;
  }
  std::cout << sum_sizes << std::endl;

  return 0;
}
