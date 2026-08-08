#include "object.hpp"

namespace goon::object {

Object::Object(
    mesh::Mesh mesh,
    const material::Material& material,
    matrix::Matrix<float, 4, 4> transform
)
    // NOLINTNEXTLINE(performance-move-const-arg)
    : transform{std::move(transform)}
    , mesh{std::move(mesh)}
    , material{material} {}

auto Object::draw(const camera::Camera& camera) const -> void {
    this->material.bind(this->transform, camera.transform, camera.projection);
    this->mesh.draw();
}

} // namespace goon::object
