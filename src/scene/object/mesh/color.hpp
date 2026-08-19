#pragma once

namespace goon::scene::object::mesh {

struct Color final {
    using Value = float;
    constexpr static auto DIMENSION{4};

    Value r{1};
    Value g{1};
    Value b{1};
    Value a{1};

    constexpr Color() = default;

    constexpr Color(const Value r, const Value g, const Value b, const Value a)
        : r{r}
        , g{g}
        , b{b}
        , a{a} {}
};

} // namespace goon::scene::object::mesh
