#pragma once

#include "camera/camera.hpp"
#include "material/material.hpp"
#include "mesh/mesh.hpp"

namespace goon::object {

class Object final {
  public:
    transform::Transform transform;

    Object(
        mesh::Mesh mesh,
        const material::Material& material,
        transform::Transform transform
    );

    Object(const Object&) = delete;
    Object(Object&&) = delete;

    ~Object() = default;

    auto operator=(const Object&) -> Object& = delete;
    auto operator=(Object&&) -> Object& = delete;

    auto draw(const camera::Camera& camera) const -> void;

  private:
    mesh::Mesh mesh;
    const material::Material& material;
};

} // namespace goon::object
