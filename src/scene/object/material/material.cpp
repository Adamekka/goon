#include "material.hpp"

namespace goon::scene::object::material {

Material::Material(
    shader::ShaderProgram& shader_program,
    const texture::Texture& texture,
    const float shininess
)
    : shininess{shininess}
    , shader_program{&shader_program}
    , texture{&texture} {
    core::assert_that(std::isfinite(shininess));
    core::assert_that(shininess >= 0.0f);
}

auto Material::unbind() -> void {
    texture::Texture::unbind();
    shader::ShaderProgram::unbind();
}

} // namespace goon::scene::object::material
