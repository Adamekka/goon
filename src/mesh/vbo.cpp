#include "vbo.hpp"
#include "gl.hpp"

namespace goon::mesh {

VBO::VBO(const std::span<const Point> vertices) {
    glGenBuffers(1, &this->id);
    this->bind();
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<int64_t>(sizeof(Point) * vertices.size()),
        vertices.data(),
        GL_STATIC_DRAW
    );
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->id);
}

auto VBO::bind() const -> void {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

auto VBO::unbind() -> void {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace goon::mesh
