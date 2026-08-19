#pragma once

#include "core/assert.hpp"

namespace goon::math {

template<std::floating_point T, size_t Size>
[[nodiscard]] constexpr auto normalize(const std::array<T, Size>& values)
    -> std::array<T, Size> {
    auto length{T{}};
    for (const auto value : values) {
        length = std::hypot(length, value);
    }
    core::assert_that(std::isfinite(length));
    core::assert_that(length > 0);

    auto result{values};
    for (auto& value : result) {
        value /= length;
    }
    return result;
}

template<typename T, size_t Size>
    requires(std::integral<T> || std::floating_point<T>)
[[nodiscard]] constexpr auto
dot(const std::array<T, Size>& left, const std::array<T, Size>& right) -> T {
    auto result{T{}};
    for (size_t index{0}; index < Size; ++index) {
        result += left[index] * right[index];
    }
    return result;
}

template<typename T>
    requires(std::integral<T> || std::floating_point<T>)
[[nodiscard]] constexpr auto
cross(const std::array<T, 3>& left, const std::array<T, 3>& right)
    -> std::array<T, 3> {
    return std::array<T, 3>{
        static_cast<T>((left[1] * right[2]) - (left[2] * right[1])),
        static_cast<T>((left[2] * right[0]) - (left[0] * right[2])),
        static_cast<T>((left[0] * right[1]) - (left[1] * right[0]))
    };
}

} // namespace goon::math
