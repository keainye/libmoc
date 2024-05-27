#ifndef __MOC_CHANNEL_H
#define __MOC_CHANNEL_H

#include <mutex>
#include <utility>
#include <queue>
#include <memory>
#include "semaphore.h"

namespace moc {

template <typename T, int _cap = 0>
class channel {
public:
  int size, cap;
  static std::shared_ptr<channel> make();
  virtual void operator<<(T _value) = 0;
  virtual void operator>>(T &_value) = 0;
};

template <typename T, int _cap = 0>
static std::shared_ptr<channel> channel::make() {
  if (_cap == 0) 
    return std::shared_ptr<channel>(new nbchannel<T>);
  return std::shared_ptr<channel>(new bchannel<T, _cap>);
}

template <typename T>
class nbchannel: public channel<T> {
  std::queue<std::pair<std::mutex*, T>*> read, write;
  std::mutex clock;
 public:
  nbchannel(): size(0), cap(0) {}
  void operator<<(T _value);
  void operator>>(T &_value);
};

// write
template <typename T>
void nbchannel<T>::operator<<(T _value) {
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
void nbchannel<T>::operator>>(T &_value) {
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
class bchannel {
  T *content;
  int cptr;
  std::mutex clock;
  semaphore<_cap> full, empty(_cap);
public:
  bchannel(): size(0), cap(_cap), cptr(0);
  ~bchannel();
  void operator<<(T _value);
  void operator>>(T &_value);
};

template<typename T, int _cap>
bchannel<T, _cap>::bchannel(): cap(_cap), size(0), cptr(0) {
  content = new T[_cap];
}

template<typename T, int _cap>
bchannel<T, _cap>::~bchannel() {
  delete[] content;
}


// write
template<typename T, int _cap>
void bchannel<T, _cap>::operator<<(T _value) {
  empty.acquire();
  clock.lock();
  content[cptr++] = _value;
  clock.unlock();
  full.release();
}

// read
template<typename T, int _cap>
void bchannel<T, _cap>::operator>>(T &_value) {
  full.acquire();
  clock.lock();
  _value = content[--cptr];
  clock.unlock();
  empty.release();
}

};  // namespace moc

#endif