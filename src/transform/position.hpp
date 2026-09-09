#pragma once

#include "goon/math/vector.hpp"

namespace goon::transform {

struct Position final {
    using Value = float;

    Value x{0.0f};
    Value y{0.0f};
    Value z{0.0f};

    constexpr Position() = default;

    constexpr Position(const Value x, const Value y, const Value z)
        : x{x}
        , y{y}
        , z{z} {
        core::assert_that(std::isfinite(x));
        core::assert_that(std::isfinite(y));
        core::assert_that(std::isfinite(z));
    }

    // NOLINTNEXTLINE(fuchsia-overloaded-operator)
    constexpr auto operator==(const Position& other) const -> bool = default;

    [[nodiscard]] constexpr auto as_vector() const -> math::Vector<Value> {
        return math::Vector<Value>{this->x, this->y, this->z};
    }
};

} // namespace goon::transform
