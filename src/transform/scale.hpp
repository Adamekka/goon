#pragma once

#include "goon/core/assert.hpp"

namespace goon::transform {

struct Scale final {
    using Value = float;

    Value x{1.0f};
    Value y{1.0f};
    Value z{1.0f};

    constexpr Scale() = default;

    constexpr Scale(const Value x, const Value y, const Value z)
        : x{x}
        , y{y}
        , z{z} {
        core::assert_ne(x, 0.0f);
        core::assert_ne(y, 0.0f);
        core::assert_ne(z, 0.0f);
        core::assert_that(std::isfinite(x));
        core::assert_that(std::isfinite(y));
        core::assert_that(std::isfinite(z));
    }

    // NOLINTNEXTLINE(fuchsia-overloaded-operator)
    constexpr auto operator==(const Scale& other) const -> bool = default;

    [[nodiscard]] constexpr auto to_array() const -> std::array<Value, 3> {
        return std::array{this->x, this->y, this->z};
    }
};

} // namespace goon::transform
