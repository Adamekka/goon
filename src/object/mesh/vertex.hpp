#pragma once

#include "color.hpp"
#include "pos.hpp"
#include "texture_coordinates.hpp"

namespace goon::object::mesh {

struct Vertex final {
    Pos position;
    Color color;
    TextureCoordinates texture_coordinates;

    Vertex() = default;

    constexpr Vertex(
        const Pos position,
        const Color color,
        const TextureCoordinates texture_coordinates
    )
        : position{position}
        , color{color}
        , texture_coordinates{texture_coordinates} {}
};

} // namespace goon::object::mesh
