#pragma once

#include "vao.hpp"
#include <vector>

namespace goon {

struct Mesh final {
    std::vector<Point> vertices;
    const VBO vbo{this->vertices};
    const VAO vao{this->vbo};

    explicit constexpr Mesh(std::span<const Point> vertices)
        : vertices{vertices.begin(), vertices.end()} {}

    auto draw() const -> void;
};

} // namespace goon
