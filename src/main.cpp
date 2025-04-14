// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

std::string infx2pstfx(const std::string& inf);
int eval(const std::string& post);

int main() {
  std::string expr;
  std::getline(std::cin, expr);

  std::string post = infx2pstfx(expr);
  std::cout << post << "\n";
  std::cout << eval(post) << "\n";

  return 0;
}
