#include "log.h"
#include <stdarg.h>
#include <ctime>
#include <chrono>

namespace moc {
void _print_time() {
	auto now = std::chrono::system_clock::now();
	auto timestamp = std::chrono::system_clock::to_time_t(now);
	std::tm local_time = *std::localtime(&timestamp);

	auto duration = now.time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
	std::printf(
		"\033[34m%04d-%02d-%02d %02d:%02d:%02d.%03d\033[0m",
		local_time.tm_year + 1900,
		local_time.tm_mon + 1,
		local_time.tm_mday,
		local_time.tm_hour,
		local_time.tm_min,
		local_time.tm_sec,
		millis.count()
	);
}

void log(std::string msg) {
	_print_time();
	std::printf("\033[32m [I] \n\033[0m%s", msg.c_str());
}

void warn(std::string msg) {
	_print_time();
	std::printf("\033[33m [W] \n\033[0m%s", msg.c_str());
}

void panic(std::string msg) {
	_print_time();
	std::printf("\033[31m [E] \n\033[0m%s", msg.c_str());
	exit(1);
}

void logf(const char *fmt, ...) {
	_print_time();
	va_list args;
	va_start(args, fmt);
	std::printf("\033[32m [I] ");
	std::printf("\033[0m");
	std::vprintf(fmt, args);
	va_end(args);
}

void warnf(const char *fmt, ...) {
	_print_time();
	va_list args;
	va_start(args, fmt);
	std::printf("\033[33m [W] ");
	std::printf("\033[0m");
	std::vprintf(fmt, args);
	va_end(args);
}

void panicf(const char *fmt, ...) {
	_print_time();
	va_list args;
	va_start(args, fmt);
	std::printf("\033[31m [E] ");
	std::printf("\033[0m");
	std::vprintf(fmt, args);
	va_end(args);
	exit(1);
}
}