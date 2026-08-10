#pragma once

#include "object/object.hpp"
#include <plf_hive/plf_hive.h>

namespace goon::scene {

class Scene final {
  public:
    light::Light light;
    camera::Camera camera;
    plf::hive<object::Object> objects;

    Scene() = default;

    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    ~Scene() = default;

    auto operator=(const Scene&) -> Scene& = delete;
    auto operator=(Scene&&) -> Scene& = delete;

    auto update() const -> void;

    [[nodiscard]] constexpr auto create_camera(
        const transform::Transform transform = transform::Transform{},
        const float fov_radians = std::numbers::pi_v<float> / 4.0f,
        const float aspect_ratio = 4.0f / 3.0f,
        const float z_near = 0.1f,
        const float z_far = 100.0f
    ) -> camera::Camera& {
        this->camera = camera::Camera{
            transform, fov_radians, aspect_ratio, z_near, z_far
        };
        return this->camera;
    }

    [[nodiscard]] constexpr auto create_light(
        const std::optional<light::AmbientLight> ambient_light = std::nullopt
    ) -> light::Light& {
        this->light = light::Light{ambient_light};
        return this->light;
    }

    [[nodiscard]] auto create_object(
        object::mesh::Mesh mesh,
        const object::material::Material& material,
        transform::Transform transform
    ) -> object::Object*;
};

} // namespace goon::scene
