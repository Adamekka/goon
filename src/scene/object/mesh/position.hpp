#pragma once

#include <cstddef>

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
};

} // namespace goon::scene::object::mesh
