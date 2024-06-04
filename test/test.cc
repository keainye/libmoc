#include "test.h"

#include <clock.h>

int main() {
  while (true) {
    printf("enter while\n");
    int i = 10000;
    while (i--);
    printf("finish compute\n");
    moc::tick(1000);
  }
  return 0;
}
