#pragma once

#include "shader/shader_program.hpp"
#include "texture/texture.hpp"

namespace goon::object::material {

class Material final {
  public:
    Material(
        shader::ShaderProgram& shader_program, const texture::Texture& texture
    );

    Material(const Material&) = delete;
    Material(Material&&) = delete;

    ~Material() = default;

    auto operator=(const Material&) -> Material& = delete;
    auto operator=(Material&&) -> Material& = delete;

    template<shader::detail::ShaderData T>
    auto bind(const T& transform) const -> void {
        this->shader_program.bind();
        this->shader_program.get_args().at("transform").set_uniform(transform);

        this->texture.bind();
    }

    static auto unbind() -> void;

  private:
    shader::ShaderProgram& shader_program;
    const texture::Texture& texture;
};

} // namespace goon::object::material
