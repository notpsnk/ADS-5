// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

std::string infx2pstfx(const std::string& inf);
int eval(const std::string& post);

int main() {
  std::string inputExpression;

  if (std::getline(std::cin, inputExpression)) {
    auto postfixForm = infx2pstfx(inputExpression);
    std::cout << postfixForm << std::endl;
    std::cout << eval(postfixForm) << std::endl;
  }

  return 0;
}
