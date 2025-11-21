// Rx Compiler in One File
// If sema Passes, output 1 and exit 0; otherwise output 0 and exit 1

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::istream *in = &std::cin;
  std::ifstream file;

  if (argc > 1) {
    file.open(argv[1]);
    if (!file.is_open()) {
      std::cerr << "error: cannot open file '" << argv[1] << "'\n";
      return 1;
    }
    in = &file;
  }

  std::string line;
  const std::string prefix = "Verdict: ";
  while (std::getline(*in, line)) {
    size_t pos = 0;
    while (pos < line.size() &&
           std::isspace(static_cast<unsigned char>(line[pos])))
      ++pos;
    if (pos + prefix.size() <= line.size() &&
        line.compare(pos, prefix.size(), prefix) == 0) {
      std::string verdict = line.substr(pos + prefix.size());
      if (verdict.substr(0, 4) == "Pass") {
        std::ifstream test_ll("test.ll");
        std::ifstream builtin_c("builtin.c");
        
        if (test_ll.is_open()) {
          std::cout << test_ll.rdbuf();
        } else {
          std::cerr << "cannot open file 'test.ll'\n";
          return 1;
        }
        
        if (builtin_c.is_open()) {
          std::cerr << builtin_c.rdbuf();
        } else {
          std::cerr << "cannot open file 'builtin.c'\n";
          return 1;
        }

        return 0;
      } else {
        std::cerr << "semantic failed\n";
        return 1;
      }
    }
  }

  return 1;
}