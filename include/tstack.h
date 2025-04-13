// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int maxSize>
class TStack {
private:
  T data[maxSize];
  int topIndex;
public:
  TStack() : topIndex(-1) {}
  void push(const T& value) {
    if (isFull()) {
      throw std::overflow_error("Stack overflow");
    }
    data[++topIndex] = value;
  }
  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack underflow");
    }
    --topIndex;
  }
  T top() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return data[topIndex];
  }
  bool isEmpty() const {
    return topIndex == -1;
  }
  bool isFull() const {
    return topIndex == maxSize - 1;
  }
};
#endif  // INCLUDE_TSTACK_H_
