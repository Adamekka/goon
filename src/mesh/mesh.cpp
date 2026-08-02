#include "mesh.hpp"
#include "gl.hpp"

namespace goon::mesh {

Mesh::Mesh(
    const std::span<const Vertex> vertices,
    std::shared_ptr<const Texture> texture
)
    : vertices{vertices.begin(), vertices.end()}
    , texture{std::move(texture)} {}

auto Mesh::draw() const -> void {
    this->texture->bind();
    this->vao.bind();

    glDrawArrays(
        GL_TRIANGLE_STRIP, 0, static_cast<int32_t>(this->vertices.size())
    );
}

} // namespace goon::mesh
