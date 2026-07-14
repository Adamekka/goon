#include "mesh.hpp"
#include "gl.hpp"
#include "vao.hpp"

namespace goon {

auto Mesh::draw() const -> void {
    const auto vbo{VBO{this->vertices}};
    const auto vao{VAO{vbo}};

    glDrawArrays(
        GL_TRIANGLE_STRIP, 0, static_cast<int32_t>(this->vertices.size())
    );
}

} // namespace goon
