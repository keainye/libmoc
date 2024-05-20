#include "log.h"

namespace moc {
void log(std::string msg) {
  std::printf("\033[32m[I] %s\n\033[0m", msg.c_str());
}

void warn(std::string msg) {
  std::printf("\033[33m[W] %s\n\033[0m", msg.c_str());
}

void panic(std::string msg) {
  std::printf("\033[31m[E] %s\n\033[0m", msg.c_str());
  exit(1);
}
}