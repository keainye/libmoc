#include "mocutils.h"
#include "strings.h"
#include "iostream"

int main() {
  std::string s("123456789");
  std::cout << moc::strrev(s) << std::endl;
  return 0;
}
