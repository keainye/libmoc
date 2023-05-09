#include "mocutils.h"

#include "iostream"

void moc::hello() {
  std::cout << "hello from moc" << std::endl;
}

moc::bytes::bytes(int _len): length(_len) {
  this->_bytes = new byte[_len];
}

moc::bytes::bytes(int _len, byte* _b): length(_len) {
  this->_bytes = new byte[_len];
  for (int i = 0; i < _len; i++)
    this->_bytes[i] = _b[i];
}

moc::bytes::~bytes() {
  delete[] _bytes;
}

moc::byte& moc::bytes::operator[](int _i) {
  return _bytes[_i];
}