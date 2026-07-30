#include "panic.hpp"
#include <print>
#include <source_location>

namespace goon::core {

[[noreturn]] auto panic(const std::string_view message) -> void {
    constexpr auto LOCATION{std::source_location::current()};

    std::println(
        "PANIC: {{}}\n  at {{}}:{{}} in {{}}",
        message,
        LOCATION.file_name(),
        LOCATION.line(),
        LOCATION.function_name()
    );

    std::abort();
}

} // namespace goon::core
