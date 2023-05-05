#include "strings.h"

std::string moc::strrev(std::string _src) {
  char *c = new char[_src.size()+1];
  int ptr = 0;
  for (int i = _src.size()-1; i >= 0; i--)
    c[ptr++] = _src[i];
  c[ptr] = 0;
  std::string ret(c);
  delete[] c;
  return ret;
}