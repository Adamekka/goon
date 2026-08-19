#include "panic.hpp"
#include <execinfo.h>
#include <print>

namespace goon::core {

auto panic(const std::string_view message, const std::source_location location)
    -> void {
    std::println(
        stderr,
        "PANIC: {}\n  at {}:{} in {}\n\nStack trace:",
        message,
        location.file_name(),
        location.line(),
        location.function_name()
    );
    auto _{std::fflush(stderr)};

    // Stack trace stores at most 64 frames
    auto frames{std::array<void*, 64>{}};
    const auto frame_count{backtrace(frames.data(), frames.size())};
    if (frame_count > 0) {
        backtrace_symbols_fd(frames.data(), frame_count, fileno(stderr));
    }

    std::abort();
}

} // namespace goon::core
