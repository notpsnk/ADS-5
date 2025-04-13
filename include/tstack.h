// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int SIZE>
class TStack {
private:
  T data[SIZE];
  int top;

public:
  TStack() : top(-1) {}

  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == SIZE - 1;
  }

  void push(const T& value) {
    if (!isFull()) {
      data[++top] = value;
    }
  }

  T pop() {
    if (!isEmpty()) {
      return data[top--];
    }
    throw "Stack underflow!";
  }

  T peek() const {
    if (!isEmpty()) {
      return data[top];
    }
    throw "Stack is empty!";
  }
};

#endif  // INCLUDE_TSTACK_H_
