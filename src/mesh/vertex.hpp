#pragma once

#include "color.hpp"
#include "pos.hpp"

namespace goon::mesh {

struct Vertex final {
    Pos position;
    Color color;

    Vertex() = default;

    constexpr Vertex(const Pos position, const Color color)
        : position{position}
        , color{color} {}
};

} // namespace goon::mesh
