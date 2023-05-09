#include "../src/mocutils.h"
#include "cstdlib"
#include "iostream"

using namespace std;
using namespace moc;

int main() {
  bytes b(10);

  for (int i = 0; i < 10; i++)
    b[i] = i;

  for (int i = 0; i < 10; i++)
    if (b[i] != i)
      exit(1);

  for (int i = 0; i < 10; i++)
    b[i]++;

  for (int i = 0; i < 10; i++)
    if (b[i] != i + 1)
      exit(2);

  for (int i = 0; i < 10; i++)
    b[i]--;

  for (int i = 0; i < 10; i++)
    if (b[i] != i)
      exit(3);

  return 0;
}