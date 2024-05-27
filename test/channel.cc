#include "channel.h"
#include "test.h"

using namespace std;
using namespace moc;

int main() {{
  auto c = make_channel<int, 3>();
  test(c.cap == 3);
  c << 1;
  test(c.size == 1);
  c << 2;
  test(c.size == 2);
  c << 3;
  test(c.size == 3);
  int recv;
  c >> recv;
  test(c.size == 2);
  test(recv == 1);
  c >> recv;
  test(c.size == 1);
  test(recv == 2);
  c >> recv;
  test(c.size == 0);
  test(recv == 3);
  pass("bchannel");
}; {
  auto c = make_channel<int>();
  test(c.size == 0);
  test(c.cap == 0);
  pass("nbchannel");
}
  return 0;
}