// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int maxSize>
class TStack {
 public:
  TStack() : topIndex_(-1) {}

  void push(const T& value) {
    if (isFull()) throw std::overflow_error("Stack overflow");
    data_[++topIndex_] = value;
  }

  void pop() {
    if (isEmpty()) throw std::underflow_error("Stack underflow");
    --topIndex_;
  }

  T top() const {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return data_[topIndex_];
  }

  bool isEmpty() const {
    return topIndex_ == -1;
  }

  bool isFull() const {
    return topIndex_ == kMaxSize - 1;
  }

 private:
  static const int kMaxSize = maxSize;
  T data_[kMaxSize];
  int topIndex_;
};

#endif  // INCLUDE_TSTACK_H_
