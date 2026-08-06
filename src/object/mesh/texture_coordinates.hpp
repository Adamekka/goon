#pragma once

#include <array>

namespace goon::object::mesh {

struct TextureCoordinates final {
    using Value = float;
    constexpr static auto DIMENSION{2};

    Value u{0};
    Value v{0};

    TextureCoordinates() = default;

    constexpr TextureCoordinates(const Value u, const Value v)
        : u{u}
        , v{v} {}

    constexpr explicit TextureCoordinates(const std::array<Value, 2> values)
        : u{values[0]}
        , v{values[1]} {}
};

} // namespace goon::object::mesh
