#include "test.h"

#include <clock.h>
#include <log.h>

int main() {
  moc::logf("Test from %d\n", 233);
  moc::panicf("Error from %d\n", 234);
  return 0;
}
