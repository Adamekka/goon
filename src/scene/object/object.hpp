#pragma once

#include "camera/camera.hpp"
#include "material/material.hpp"
#include "mesh/mesh.hpp"

namespace goon::scene::object {

class Object final {
  public:
    transform::Transform transform;

    Object(
        mesh::Mesh mesh,
        const material::Material& material,
        transform::Transform transform
    );

    Object(const Object&) = delete;
    Object(Object&&) = default;

    ~Object() = default;

    auto operator=(const Object&) -> Object& = delete;
    auto operator=(Object&&) -> Object& = default;

    auto draw(const camera::Camera& camera, const light::Light& light) const
        -> void;

  private:
    mesh::Mesh mesh;
    const material::Material* material;
};

} // namespace goon::scene::object
