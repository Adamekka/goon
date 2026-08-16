#include "panic.hpp"
#include <print>

namespace goon::core {

auto panic(const std::string_view message, const std::source_location location)
    -> void {
    std::println(
        stderr,
        "PANIC: {}\n  at {}:{} in {}",
        message,
        location.file_name(),
        location.line(),
        location.function_name()
    );

    std::abort();
}

} // namespace goon::core
