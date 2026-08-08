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

    template<
        shader::detail::ShaderData T,
        shader::detail::ShaderData U,
        shader::detail::ShaderData V>
    auto bind(const T& model, const U& view, const V& projection) const
        -> void {
        this->shader_program.bind();
        this->shader_program.get_args().at("model").set_uniform(model);
        this->shader_program.get_args().at("view").set_uniform(view);
        this->shader_program.get_args()
            .at("projection")
            .set_uniform(projection);

        this->texture.bind();
    }

    static auto unbind() -> void;

  private:
    shader::ShaderProgram& shader_program;
    const texture::Texture& texture;
};

} // namespace goon::object::material
