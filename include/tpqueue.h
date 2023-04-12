// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T, int size>
class TPQueue {
 private:
  T* items;
  int max_size;
  int head, tail;
  int count;

 public:
  TPQueue(): max_size(size), head(0), tail(0), count(0) {
    items = new T[max_size + 1];
  }

  void push(const T& item) {
    if (count == 0) {
      items[tail++] = item;
      count++;
    } else {
      int i = tail - 1;
      bool flag = false;
      while (i >= head && item.prior > items[i].prior) {
        flag = true;
        items[i + 1] = items[i];
        items[i] = item;
        i--;
      }
      if (!flag) {
        items[tail] = item;
      }
      tail++;
      count++;
    }
    if (tail > max_size) {
      tail -= max_size + 1;
    }
  }

  const T& pop() {
    count--;
    if (head > max_size) {
      head -= max_size + 1;
    }
    return items[head++];
  }

  T& front() {
    assert(count > 0);
    return items[head];
  }

  bool isEmpty() const {
    return count == 0;
  }

  bool isFull() const {
    return count == max_size;
  }

  ~TPQueue() {
    delete[] items;
  }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_

