#pragma once

#include "vao.hpp"
#include <vector>

namespace goon::object::mesh {

class Mesh final {
  public:
    explicit Mesh(std::span<const Vertex> vertices);

    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = default;

    ~Mesh() = default;

    auto operator=(const Mesh&) -> Mesh& = delete;
    auto operator=(Mesh&&) -> Mesh& = default;

    auto draw() const -> void;

  private:
    std::vector<Vertex> vertices;
    VBO vbo{this->vertices};
    VAO vao{this->vbo};
};

} // namespace goon::object::mesh
