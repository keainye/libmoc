#include "test.h"
#include <semaphore.h>

int main() {
  moc::semaphore<2> s;
  s.release();
  printf("1");
  s.release();
  printf("1");
  s.release();
  printf("1");
  return 0;
}
