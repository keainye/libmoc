#include "../src/channel.h"
#include "test.h"

using namespace std;
using namespace moc;

int main() {
  channel<int> chan;
  chan < 233;
  int i = 123;
  chan > i;
  test(i == 233);
  pass("channel");

  return 0;
}