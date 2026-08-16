#pragma once

#include <array>

namespace goon::scene::object::mesh {

struct Color final {
    using Value = float;
    constexpr static auto DIMENSION{4};

    Value r{1};
    Value g{1};
    Value b{1};
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

} // namespace goon::scene::object::mesh
