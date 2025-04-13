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
    bool readingNumber = false;

    for (char c : inf) {
        if (isspace(c)) {
            continue;
        }

        if (isdigit(c)) {
            if (!readingNumber && !postfix.empty()) {
                postfix += ' ';
            }
            postfix += c;
            readingNumber = true;
        } else {
            if (readingNumber) {
                postfix += ' ';
                readingNumber = false;
            }

            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += stack.pop();
                    postfix += ' ';
                }
                stack.pop(); // Remove '(' from stack
            } else {
                while (!stack.isEmpty() && stack.peek() != '(' && 
                       precedence(c) <= precedence(stack.peek())) {
                    postfix += stack.pop();
                    postfix += ' ';
                }
                stack.push(c);
            }
        }
    }

    // Add remaining operators
    while (!stack.isEmpty()) {
        postfix += stack.pop();
        postfix += ' ';
    }

    // Remove trailing space if any
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack.push(std::stoi(token));
        } else {
            int right = stack.pop();
            int left = stack.pop();
            switch (token[0]) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/': stack.push(left / right); break;
            }
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
