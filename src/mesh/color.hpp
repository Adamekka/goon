#pragma once

#include <array>

namespace goon::mesh {

struct Color final {
    using Value = float;
    constexpr static auto DIMENSION{4};

    Value r{0};
    Value g{0};
    Value b{0};
    Value a{1};

    Color() = default;

    constexpr Color(const Value r, const Value g, const Value b, const Value a)
        : r{r}
        , g{g}
        , b{b}
        , a{a} {}

    constexpr explicit Color(const std::array<Value, 4> values)
        : r{values[0]}
        , g{values[1]}
        , b{values[2]}
        , a{values[3]} {}
};

} // namespace goon::mesh
