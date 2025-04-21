// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char symbol) {
  switch (symbol) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> ops;
  std::string res;

  for (std::size_t pos = 0; pos < inf.size(); ++pos) {
    char current = inf[pos];

    if (std::isdigit(current)) {
      std::string val;
      while (pos < inf.size() && std::isdigit(inf[pos])) {
        val.push_back(inf[pos]);
        ++pos;
      }
      res += val + " ";
    } else if (current == '(') {
      ops.push(current);
    } else if (current == ')') {
      while (!ops.isEmpty() && ops.top() != '(') {
        res += ops.top();
        res += ' ';
        ops.pop();
      }
      if (!ops.isEmpty()) ops.pop();
    } else if (current == '+' || current == '-' ||
      current == '*' || current == '/') {
      while (!ops.isEmpty() && precedence(ops.top()) >= precedence(current)) {
        res += ops.top();
        res += ' ';
        ops.pop();
      }
      ops.push(current);
    }
  }

  while (!ops.isEmpty()) {
    res += ops.top();
    res += ' ';
    ops.pop();
  }

  if (!res.empty())
    res.pop_back();

  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> stk;
  std::istringstream parser(post);
  std::string item;

  while (parser >> item) {
    if (std::isdigit(item[0])) {
      stk.push(std::stoi(item));
    } else {
      int rhs = stk.top(); stk.pop();
      int lhs = stk.top(); stk.pop();
      if (item[0] == '+') out = lhs + rhs;
      else if (item[0] == '-') out = lhs - rhs;
      else if (item[0] == '*') out = lhs * rhs;
      else if (item[0] == '/') out = lhs / rhs;

      stk.push(out);
    }
  }

  return stk.top();
}
