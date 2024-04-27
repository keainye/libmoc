#ifndef __MOC_CHANNEL_H
#define __MOC_CHANNEL_H

#include "mutex"

namespace moc {
template <typename T>
class channel {
  T content;
  std::mutex in, out;

 public:
  channel() { out.lock(); }
  channel(T _value) {
    content = _value;
    in.lock();
  }

  void operator<(T _value);
  void operator>(T &_value);
};

template <typename T>
void channel<T>::operator<(T _value) {
  this->in.lock();
  this->content = _value;
  this->out.unlock();
}

template <typename T>
void channel<T>::operator>(T &_value) {
  this->out.lock();
  _value = this->content;
  this->in.unlock();
}
};  // namespace moc

#endif