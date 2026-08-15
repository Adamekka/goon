#pragma once

#include "boost/hana/define_struct.hpp" // IWYU pragma: export
#include "color.hpp"
#include "normal_vector.hpp"
#include "texture_coordinates.hpp"

namespace goon::scene::object::mesh {

struct Vertex final {
    BOOST_HANA_DEFINE_STRUCT(
        Vertex,
        (Position, position),
        (Color, color),
        (TextureCoordinates, texture_coordinates),
        (NormalVector, normal_vector)
    );

    Vertex() = default;

    constexpr Vertex(
        const Position position,
        const Color color,
        const TextureCoordinates texture_coordinates,
        const NormalVector normal_vector
    )
        : position{position}
        , color{color}
        , texture_coordinates{texture_coordinates}
        , normal_vector{normal_vector} {}
};

} // namespace goon::scene::object::mesh
