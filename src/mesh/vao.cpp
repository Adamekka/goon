#include "vao.hpp"
#include "gl.hpp"

namespace goon::mesh {

VAO::VAO(const VBO& vbo) {
    glGenVertexArrays(1, &this->id);

    this->bind();
    vbo.bind();

    // MARK: Position

    // I'd like to compare with GL_FLOAT instead
    static_assert(std::same_as<Pos::Value, float>);
    glVertexAttribPointer(
        0, Pos::DIMENSION, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr
    );
    glEnableVertexAttribArray(0);

    // MARK: Color

    // I'd like to compare with GL_FLOAT instead
    static_assert(std::same_as<Color::Value, float>);
    glVertexAttribPointer(
        1,
        Color::DIMENSION,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
        // NOLINTBEGIN(performance-no-int-to-ptr)
        reinterpret_cast<const void* const>(offsetof(Vertex, color))
        // NOLINTEND(performance-no-int-to-ptr)
        // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
    );
    glEnableVertexAttribArray(1);

    // MARK: Texture Coordinates

    // I'd like to compare with GL_FLOAT instead
    static_assert(std::same_as<TextureCoordinates::Value, float>);
    glVertexAttribPointer(
        2,
        TextureCoordinates::DIMENSION,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
        // NOLINTBEGIN(performance-no-int-to-ptr)
        reinterpret_cast<const void* const>(
            offsetof(Vertex, texture_coordinates)
        )
        // NOLINTEND(performance-no-int-to-ptr)
        // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
    );
    glEnableVertexAttribArray(2);
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

} // namespace goon::mesh
