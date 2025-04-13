// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
int main() {
  std::string infix;
  std::cout << "Введите инфиксное выражение: \n";
  std::getline(std::cin, infix);
  std::string postfix;
  TStack<char, 100> opStack;
  std::istringstream in(infix);
  char ch;
  while (in >> std::noskipws >> ch) {
    if (isdigit(ch)) {
      std::string number(1, ch);
      while (in.peek() != EOF && isdigit(in.peek())) {
        char next;
        in >> next;
        number += next;
      }
      postfix += number + ' ';
    } else if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop();
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!opStack.isEmpty() &&
            precedence(opStack.top()) >= precedence(ch)) {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }
  }
  while (!opStack.isEmpty()) {
    postfix += opStack.top();
    postfix += ' ';
    opStack.pop();
  }
  std::cout << "Постфиксная форма: " << postfix << "\n";
  TStack<int, 100> valStack;
  std::istringstream postStream(postfix);
  std::string token;
  while (postStream >> token) {
    if (isdigit(token[0])) {
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
  std::cout << "Результат вычисления: " << valStack.top() << "\n";
  return 0;
}
