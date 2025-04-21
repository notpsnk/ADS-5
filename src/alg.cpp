// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string result;
  TStack<char, 100> stack;
  size_t i = 0;

  while (i < inf.length()) {
    char ch = inf[i];

    if (std::isdigit(ch)) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        result += inf[i++];
      }
      result += ' ';
      continue;
    }

    if (ch == '(') {
      stack.add(ch);
    } else if (ch == ')') {
      while (!stack.empty() && stack.peek() != '(') {
        result += stack.peek();
        result += ' ';
        stack.remove();
      }
      if (!stack.empty()) stack.remove();
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!stack.empty() && precedence(stack.peek()) >= precedence(ch)) {
        result += stack.peek();
        result += ' ';
        stack.remove();
      }
      stack.add(ch);
    }

    ++i;
  }

  while (!stack.empty()) {
    result += stack.peek();
    result += ' ';
    stack.remove();
  }

  if (!result.empty() && result.back() == ' ')
    result.pop_back();

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream in(post);
  std::string token;

  while (in >> token) {
    if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
      stack.add(std::stoi(token));
    } else {
      int b = stack.peek(); stack.remove();
      int a = stack.peek(); stack.remove();
      int result = 0;

      switch (token[0]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
      }

      stack.add(result);
    }
  }

  return stack.peek();
}
