#pragma once

#include "scene/light/light.hpp"
#include "shader/shader_program.hpp"
#include "texture/texture.hpp"

namespace goon::scene::object::material {

class Material final {
  public:
    Material(
        shader::ShaderProgram& shader_program, const texture::Texture& texture
    );

    Material(const Material&) = delete;
    Material(Material&&) = default;

    ~Material() = default;

    auto operator=(const Material&) -> Material& = delete;
    auto operator=(Material&&) -> Material& = default;

    auto bind(
        const shader::detail::ShaderData auto& model,
        const shader::detail::ShaderData auto& view,
        const shader::detail::ShaderData auto& projection,
        const light::Light& light
    ) const -> void {
        this->shader_program->bind();

        const auto& shader_args{this->shader_program->get_args()};

        shader_args.at("model").set_uniform(model);
        shader_args.at("view").set_uniform(view);
        shader_args.at("projection").set_uniform(projection);

        if (light.ambient_light.has_value()) {
            shader_args.at("ambient_light_color")
                .set_uniform(light.ambient_light->color);
            shader_args.at("ambient_strength")
                .set_uniform(light.ambient_light->intensity);
        } else {
            shader_args.at("ambient_light_color")
                .set_uniform(std::array{1.0f, 1.0f, 1.0f});
            shader_args.at("ambient_strength").set_uniform(1.0f);
        }

        this->texture->bind();
    }

    static auto unbind() -> void;

  private:
    shader::ShaderProgram* shader_program;
    const texture::Texture* texture;
};

} // namespace goon::scene::object::material
