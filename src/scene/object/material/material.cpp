#include "material.hpp"

namespace goon::scene::object::material {

Material::Material(
    shader::ShaderProgram& shader_program, const texture::Texture& texture
)
    : shader_program{&shader_program}
    , texture{&texture} {}

auto Material::unbind() -> void {
    texture::Texture::unbind();
    shader::ShaderProgram::unbind();
}

} // namespace goon::scene::object::material
