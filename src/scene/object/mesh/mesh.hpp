#pragma once

#include "mesh_draw_mode.hpp"
#include "vao.hpp"
#include <vector>

namespace goon::scene::object::mesh {

class Mesh final {
  public:
    constexpr explicit Mesh(
        const std::span<const Vertex> vertices, const MeshDrawMode draw_mode
    )
        : vertices{vertices.begin(), vertices.end()}
        , draw_mode{draw_mode} {}

    explicit Mesh(std::vector<Vertex>&& vertices, MeshDrawMode draw_mode)
        : vertices{std::move(vertices)}
        , draw_mode{draw_mode} {}

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

    MeshDrawMode draw_mode;
};

} // namespace goon::scene::object::mesh
