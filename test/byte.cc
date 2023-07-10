#include "../src/byte.h"
#include "test.h"

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

  test(b.range(0, 3) + bytes("345") == bytes("012345"));
  pass("bytes& operator+(const bytes&, const bytes&)");

  b = bytes("012345");
  test(b.range(3, 7) == bytes("345"));
  pass("bytes range(bytes&, int, int)");

  b[3] = 0;
  test(b.has_next());
  test(b.next_string() == "012");
  test(b.next_string() == "45");
  pass("b.next_string()");

  test(!b.has_next());
  pass("b.has_next()");

  bytes hex(3);
  hex[0] = 0xA1;
  hex[1] = 0xB2;
  hex[2] = 0xC3;
  test(hex.to_hex_str() == "A1B2C3");
  pass("bytes.to_hex_str()");

  b = bytes(8);
  b[0] = 0x12;
  b[1] = 0x34;
  b[2] = 0x56;
  b[3] = 0x78;
  b[4] = 0xA1;
  b[5] = 0xB2;
  b[6] = 0xC3;
  b[7] = 0xD4;
  test(b.next_int32() == 0x78563412);
  test(b.next_int32() == 0xD4C3B2A1);
  pass("b.next_int32()");

  struct _tmp {int a, b, c;};
  _tmp t1{1, 2, 3}, t2{4, 5, 6};
  bytes b_tmp(&t1, sizeof(_tmp));
  b_tmp.to_mem(&t2, sizeof(_tmp));
  test(t1.a == t2.a);
  test(t1.b == t2.b);
  test(t1.c == t2.c);
  pass("addr cast");

  return 0;
}