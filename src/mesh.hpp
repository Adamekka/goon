#pragma once

#include "point.hpp"
#include <span>
#include <vector>

namespace goon {

struct Mesh final {
    std::vector<Point> vertices;

    explicit constexpr Mesh(std::span<const Point> vertices)
        : vertices{vertices.begin(), vertices.end()} {}

    auto draw() const -> void;
};

} // namespace goon
