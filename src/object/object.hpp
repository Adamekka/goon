#pragma once

#include "material/material.hpp"
#include "mesh/mesh.hpp"

namespace goon::object {

class Object final {
  public:
    matrix::Matrix<float, 4, 4> transform;

    Object(
        mesh::Mesh mesh,
        const material::Material& material,
        matrix::Matrix<float, 4, 4> transform
    );

    Object(const Object&) = delete;
    Object(Object&&) = delete;

    ~Object() = default;

    auto operator=(const Object&) -> Object& = delete;
    auto operator=(Object&&) -> Object& = delete;

    auto draw() const -> void;

  private:
    mesh::Mesh mesh;
    const material::Material& material;
};

} // namespace goon::object
