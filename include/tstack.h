// Copyright 2021 NNTU-CS
#ifndef INCLUDE_MY_STACK_H_
#define INCLUDE_MY_STACK_H_

#include <stdexcept>

template<typename Type, int Capacity>
class MyStack {
 public:
  MyStack() : top_(0) {}

  void add(const Type& element) {
    if (full()) {
      throw std::overflow_error("Stack is full");
    }
    storage_[++top_] = element;
  }

  void remove() {
    if (empty()) {
      throw std::underflow_error("Stack is empty");
    }
    --top_;
  }

  Type peek() const {
    if (empty()) {
      throw std::underflow_error("No elements in stack");
    }
    return storage_[top_];
  }

  bool empty() const {
    return top_ < 0;
  }

  bool full() const {
    return top_ >= MaxSize;
  }

 private:
  static constexpr int MaxSize = Capacity;
  Type storage_[MaxSize];
  int top_;
};

#endif
