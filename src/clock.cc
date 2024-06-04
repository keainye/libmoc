#include "clock.h"

#include <chrono>
#include <cstdlib>
#include <thread>

static i64 last;

i64 moc::get_tick() {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

void moc::tick(i64 period_time) {
  auto now = moc::get_tick();
  auto used = now - last;
  last = now;
  auto should_wait = period_time - used;
  if (should_wait <= 0) return;
  std::this_thread::sleep_for(std::chrono::milliseconds(should_wait));
}
