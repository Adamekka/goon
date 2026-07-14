#include "vao.hpp"
#include "gl.hpp"

namespace goon {

VAO::VAO(const VBO& vbo) {
    glGenVertexArrays(1, &this->id);

    this->bind();
    vbo.bind();

    // I'd like to compare with GL_FLOAT instead
    static_assert(std::same_as<Point::Value, float>);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), nullptr);
    glEnableVertexAttribArray(0);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &this->id);
}

auto VAO::bind() const -> void {
    glBindVertexArray(this->id);
}

auto VAO::unbind() -> void {
    glBindVertexArray(0);
}

} // namespace goon
