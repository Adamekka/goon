#pragma once

#include "scene/light/light.hpp"
#include "shader/shader_program.hpp"
#include "texture/texture.hpp"

namespace goon::scene::object::material {

class Material final {
  public:
    float shininess;

    Material(
        shader::ShaderProgram& shader_program,
        const texture::Texture& texture,
        float shininess
    );

    Material(const Material&) = default;
    Material(Material&&) = default;

    ~Material() = default;

    auto operator=(const Material&) -> Material& = default;
    auto operator=(Material&&) -> Material& = default;

    auto bind(
        const shader::detail::ShaderData auto& model,
        const shader::detail::ShaderData auto& normal_matrix,
        const shader::detail::ShaderData auto& view,
        const shader::detail::ShaderData auto& projection,
        const shader::detail::ShaderData auto& camera_position,
        const light::Light& light
    ) const -> void {
        this->shader_program->bind();

        const auto& shader_args{this->shader_program->get_args()};

        shader_args.at("model").set_uniform(model);
        shader_args.at("normal_matrix").set_uniform(normal_matrix);
        shader_args.at("view").set_uniform(view);
        shader_args.at("projection").set_uniform(projection);
        shader_args.at("camera_position").set_uniform(camera_position);
        shader_args.at("shininess").set_uniform(this->shininess);

        if (light.ambient_light.has_value()) {
            shader_args.at("ambient_color")
                .set_uniform(
                    std::array{
                        light.ambient_light->r,
                        light.ambient_light->g,
                        light.ambient_light->b
                    }
                );
            shader_args.at("ambient_intensity")
                .set_uniform(light.ambient_light->intensity);
        } else {
            shader_args.at("ambient_color")
                .set_uniform(std::array{1.0f, 1.0f, 1.0f});
            shader_args.at("ambient_intensity").set_uniform(0.0f);
        }

        if (light.diffuse_light.has_value()) {
            shader_args.at("diffuse_color")
                .set_uniform(
                    std::array{
                        light.diffuse_light->r,
                        light.diffuse_light->g,
                        light.diffuse_light->b
                    }
                );
            shader_args.at("diffuse_intensity")
                .set_uniform(light.diffuse_light->intensity);
            shader_args.at("diffuse_direction")
                .set_uniform(light.diffuse_light->direction);
        } else {
            shader_args.at("diffuse_color")
                .set_uniform(std::array{0.0f, 0.0f, 0.0f});
            shader_args.at("diffuse_intensity").set_uniform(0.0f);
            // The intensity disables this light, but the shader still
            // normalizes its direction, so keep that operation defined.
            shader_args.at("diffuse_direction")
                .set_uniform(std::array{0.0f, 0.0f, 1.0f});
        }

        if (light.specular_light.has_value()) {
            shader_args.at("specular_color")
                .set_uniform(
                    std::array{
                        light.specular_light->r,
                        light.specular_light->g,
                        light.specular_light->b
                    }
                );
            shader_args.at("specular_intensity")
                .set_uniform(light.specular_light->intensity);
            shader_args.at("specular_direction")
                .set_uniform(light.specular_light->direction);
        } else {
            shader_args.at("specular_color")
                .set_uniform(std::array{0.0f, 0.0f, 0.0f});
            shader_args.at("specular_intensity").set_uniform(0.0f);
            // The intensity disables this light, but the shader still
            // normalizes its direction, so keep that operation defined.
            shader_args.at("specular_direction")
                .set_uniform(std::array{0.0f, 0.0f, 1.0f});
        }

        this->texture->bind();
    }

    static auto unbind() -> void;

  private:
    shader::ShaderProgram* shader_program;
    const texture::Texture* texture;
};

} // namespace goon::scene::object::material
