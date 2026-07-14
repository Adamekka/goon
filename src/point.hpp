#pragma once

#include <array>

namespace goon {

struct Point final {
    using Value = float;

    Value x{0};
    Value y{0};
    Value z{0};

    Point() = default;

    constexpr Point(Value x, Value y, Value z)
        : x{x}
        , y{y}
        , z{z} {}

    explicit constexpr Point(std::array<Value, 3> values)
        : x{values[0]}
        , y{values[1]}
        , z{values[2]} {}
};

} // namespace goon
