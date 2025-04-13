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

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string postfix;
    bool prevWasDigit = false;

    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            if (prevWasDigit) {
                postfix += c;
            } else {
                if (!postfix.empty()) postfix += ' ';
                postfix += c;
            }
            prevWasDigit = true;
        } else {
            prevWasDigit = false;

            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += ' ';
                    postfix += stack.pop();
                }
                if (!stack.isEmpty()) stack.pop();
            } else {
                while (!stack.isEmpty() && stack.peek() != '(' && 
                       precedence(c) <= precedence(stack.peek())) {
                    postfix += ' ';
                    postfix += stack.pop();
                }
                postfix += ' ';
                stack.push(c);
            }
        }
    }

    while (!stack.isEmpty()) {
        postfix += ' ';
        postfix += stack.pop();
    }

    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (token == "+") {
            int b = stack.pop();
            int a = stack.pop();
            stack.push(a + b);
        } else if (token == "-") {
            int b = stack.pop();
            int a = stack.pop();
            stack.push(a - b);
        } else if (token == "*") {
            int b = stack.pop();
            int a = stack.pop();
            stack.push(a * b);
        } else if (token == "/") {
            int b = stack.pop();
            int a = stack.pop();
            stack.push(a / b);
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.isEmpty() ? 0 : stack.pop();
}

int main() {
  std::string infix;
  std::getline(std::cin, infix);
  std::string postfix = infx2pstfx(infix);
  std::cout << postfix << "\n" << eval(postfix) << "\n";
  return 0;
}
