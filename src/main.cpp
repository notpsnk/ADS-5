// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int main() {
  std::string inf;
  std::getline(std::cin, inf);

  std::string post;
  TStack<char, 100> opStack;
  size_t i = 0;

  while (i < inf.length()) {
    char ch = inf[i];

    if (isdigit(ch)) {
      std::string num;
      while (i < inf.length() && isdigit(inf[i])) {
        num += inf[i];
        ++i;
      }
      post += num + ' ';
      continue;
    }

    if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        post += opStack.top();
        post += ' ';
        opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop(); // убираем '('
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      auto precedence = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
      };

      while (!opStack.isEmpty() && precedence(opStack.top()) >= precedence(ch)) {
        post += opStack.top();
        post += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }

    ++i;
  }

  while (!opStack.isEmpty()) {
    post += opStack.top();
    post += ' ';
    opStack.pop();
  }

  std::cout << post << std::endl;

  std::istringstream in(post);
  std::string token;
  TStack<int, 100> valStack;

  while (in >> token) {
    if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
      valStack.push(std::stoi(token));
    } else {
      int b = valStack.top(); valStack.pop();
      int a = valStack.top(); valStack.pop();
      int result = 0;

      switch (token[0]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
      }

      valStack.push(result);
    }
  }

  std::cout << valStack.top() << std::endl;
  return 0;
}
