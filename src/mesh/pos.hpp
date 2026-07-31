#pragma once

#include <array>

namespace goon::mesh {

struct Pos final {
    using Value = float;
    constexpr static auto DIMENSION{3};

    Value x{0};
    Value y{0};
    Value z{0};

    Pos() = default;

    constexpr Pos(const Value x, const Value y, const Value z)
        : x{x}
        , y{y}
        , z{z} {}

    constexpr explicit Pos(const std::array<Value, 3> values)
        : x{values[0]}
        , y{values[1]}
        , z{values[2]} {}
};

} // namespace goon::mesh
