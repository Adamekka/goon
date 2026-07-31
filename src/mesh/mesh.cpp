#include "mesh.hpp"
#include "gl.hpp"

namespace goon::mesh {

Mesh::Mesh(const std::span<const Vertex> vertices)
    : vertices{vertices.begin(), vertices.end()} {}

auto Mesh::draw() const -> void {
    this->vao.bind();

    glDrawArrays(
        GL_TRIANGLE_STRIP, 0, static_cast<int32_t>(this->vertices.size())
    );
}

} // namespace goon::mesh
