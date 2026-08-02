#pragma once

#include "texture.hpp"
#include "vao.hpp"
#include <vector>

namespace goon::mesh {

class Mesh final {
  public:
    Mesh(
        std::span<const Vertex> vertices, std::shared_ptr<const Texture> texture
    );

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
    std::shared_ptr<const Texture> texture;
};

} // namespace goon::mesh
