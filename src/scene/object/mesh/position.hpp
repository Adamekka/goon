#pragma once

#include <array>

namespace goon::scene::object::mesh {

struct Position final {
    using Value = float;
    constexpr static size_t DIMENSION{3};

    Value x{0};
    Value y{0};
    Value z{0};

    constexpr Position() = default;

    constexpr Position(const Value x, const Value y, const Value z)
        : x{x}
        , y{y}
        , z{z} {}

    constexpr explicit Position(const std::array<Value, 3> values)
        : x{values[0]}
        , y{values[1]}
        , z{values[2]} {}
};

} // namespace goon::scene::object::mesh
