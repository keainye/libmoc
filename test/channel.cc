#include "../src/channel.h"
#include "test.h"

using namespace std;
using namespace moc;

int main() {
  moc::channel<int, 3> c;
  c << 1;
  c << 2;
  c << 3;
  int recv;
  c >> recv;
  test(recv == 1);
  c >> recv;
  test(recv == 2);
  c >> recv;
  test(recv == 3);
  pass("channel<typename, int>");
  return 0;
}