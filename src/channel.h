#ifndef __MOC_CHANNEL_H
#define __MOC_CHANNEL_H

#include <mutex>
#include <utility>
#include <queue>
#include "semaphore.h"

namespace moc {

template <typename T>
class channel {
  std::queue<std::pair<std::mutex*, T>*> read, write;
  std::mutex clock;
 public:
  void operator<<(T _value);
  void operator>>(T &_value);
};

// write
template <typename T>
void channel<T>::operator<<(T _value) {
  std::pair<std::mutex*, T> *local = nullptr;
  clock.lock();
  if (read.size()) {
    read.front()->second = _value;
    read.front()->first->unlock();
    read.pop();
  } else {
    local = new std::pair{new std::mutex, _value};
    local->first->lock();
    write.push(local);
  }
  clock.unlock();
  if (local == nullptr) return;
  local->first->lock();
  delete local->first;
  delete local;
}

// read
template <typename T>
void channel<T>::operator>>(T &_value) {
  std::pair<std::mutex*, T> *local = nullptr;
  clock.lock();
  if (write.size()) {
    _value = write.front()->second;
    write.front()->first->unlock();
    write.pop();
  } else {
    local = new std::pair{new std::mutex, _value};
    local->first->lock();
    read.push(local);
  }
  clock.unlock();
  if (local == nullptr) return;
  local->first->lock();
  _value = local->second;
  delete local->first;
  delete local;
}

template<typename T, int _cap>
class channel {
  T *content;
  int cptr;
  std::mutex clock;
  semaphore<_cap> full, empty(_cap);
public:
  int cap, size;
  channel(): cap(_cap), size(0), cptr(0);
  ~channel();
  void operator<<(T _value);
  void operator>>(T &_value);
};

template<typename T, int _cap>
channel<T, _cap>::channel(): cap(_cap), size(0), cptr(0) {
  content = new T[_cap];
}

template<typename T, int _cap>
channel<T, _cap>::~channel() {
  delete[] content;
}


// write
template<typename T, int _cap>
void channel<T, _cap>::operator<<(T _value) {
  empty.acquire();
  clock.lock();
  content[cptr++] = _value;
  clock.unlock();
  full.release();
}

// read
template<typename T, int _cap>
void channel<T, _cap>::operator>>(T &_value) {
  full.acquire();
  clock.lock();
  _value = content[--cptr];
  clock.unlock();
  empty.release();
}

};  // namespace moc

#endif