#include "mesh.hpp"
#include "gl.hpp"

namespace goon::scene::object::mesh {

auto Mesh::draw() const -> void {
    this->vao.bind();

    glDrawArrays(
        GL_TRIANGLE_STRIP, 0, static_cast<int32_t>(this->vertices.size())
    );
}

} // namespace goon::scene::object::mesh
