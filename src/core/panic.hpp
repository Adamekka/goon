#pragma once

#include <string_view>

namespace goon {

[[noreturn]] auto panic(std::string_view message) -> void;

} // namespace goon
