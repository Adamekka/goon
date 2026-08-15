#pragma once

#include <concepts>

namespace goon::core::concepts {

template<typename T>
concept FloatingScalar = std::same_as<T, float> || std::same_as<T, double>;

} // namespace goon::core::concepts
