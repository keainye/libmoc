#ifndef _MOC_BYTE
#define _MOC_BYTE

#include "vector"
#include "string"

namespace moc {
typedef unsigned char byte;

class bytes : public std::vector<byte> {
 public:
  bytes();
  bytes(int _len);
  bytes(std::string _src);
  bytes range(int start, int end);
  std::string to_string();
  bytes operator+(const bytes& other);
  std::string to_hex_str();
  void print_as_hex();
  void println_as_hex();
};
}  // namespace moc

#endif