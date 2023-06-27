#include "byte.h"
#include "iostream"

moc::bytes::bytes() : std::vector<byte>() {}

moc::bytes::bytes(int _len) : std::vector<byte>(_len) {}

moc::bytes::bytes(std::string _src) : std::vector<byte>(_src.size()+1) {
  for (int i = 0; i < _src.size(); i++)
    this->operator[](i) = _src[i];
  this->operator[](_src.size()) = 0;
}

moc::bytes moc::bytes::range(int start, int end) {
  if (end <= start) return bytes();
  if (end > this->size()) return bytes();
  int len = end-start;
  bytes ret(len);
  for (int i = 0; i < len; i++)
    ret[i] = this->operator[](start+i);
  return ret;
}

std::string moc::bytes::to_string() {
  int end = this->size();
  for (int i = 0; i < this->size(); i++) {
    if (!this->operator[](i)) {
      end = i;
      break;
    }
  }
  char str[end+1];
  for (int i = 0; i < end; i++)
    str[i] = this->operator[](i);
  str[end] = 0;
  return std::string(str);
}

moc::bytes moc::bytes::operator+(const bytes& v) {
  bytes ret(this->size()+v.size());
  int ptr = 0;
  for (int i = 0; i < this->size(); i++)
    ret[ptr++] = this->operator[](i);
  for (int i = 0; i < v.size(); i++)
    ret[ptr++] = v[i];
  return ret;
}

std::string moc::bytes::to_hex_str() {
  std::string ret;
  ret.resize(2*(this->size()));
  const char map[17] = "0123456789ABCDEF";
  int ptr = 0;
  for (int i = 0; i < this->size(); i++) {
    moc::byte val = this->operator[](i);
    ret[ptr++] = map[val>>4];
    ret[ptr++] = map[val&0x0F];
  }
  return ret;
}

void moc::bytes::print_as_hex() {
  std::cout << this->to_hex_str();
}

void moc::bytes::println_as_hex() {
  this->print_as_hex();
  std::cout << std::endl;
}
