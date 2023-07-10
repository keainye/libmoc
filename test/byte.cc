#include "test.h"
#include "../src/byte.h"

using namespace std;
using namespace moc;

int main() {
  bytes b(4);
  b[0] = '0';
  b[1] = '1';
  b[2] = '2';
  b[3] = 0;

  test(b.to_string() == "012");
  pass("to_string(bytes&)");

  test(bytes("012") == b);
  pass("to_bytes(std::string&)");

  test(b.range(0, 3)+bytes("345") == bytes("012345"));
  pass("bytes& operator+(const bytes&, const bytes&)");

  b = bytes("012345");
  test(b.range(3, 7) == bytes("345"));
  pass("bytes range(bytes&, int, int)");

  bytes hex(3);
  hex[0] = 0xA1;
  hex[1] = 0xB2;
  hex[2] = 0xC3;
  test(hex.to_hex_str() == "A1B2C3");
  pass("bytes.to_hex_str()");

  return 0;
}