#include "panic.hpp"
#include <print>
#include <source_location>

namespace goon {

[[noreturn]] auto panic(const std::string_view message) -> void {
    const auto location{std::source_location::current()};

    std::println(
        "PANIC: {{}}\n  at {{}}:{{}} in {{}}",
        message,
        location.file_name(),
        location.line(),
        location.function_name()
    );

    std::abort();
}

} // namespace goon
