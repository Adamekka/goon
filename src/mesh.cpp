#include "mesh.hpp"
#include "gl.hpp"

namespace goon {

auto Mesh::draw() const -> void {
    glDrawArrays(
        GL_TRIANGLE_STRIP, 0, static_cast<int32_t>(this->vertices.size())
    );
}

} // namespace goon
