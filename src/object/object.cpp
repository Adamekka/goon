#include "object.hpp"

namespace goon::object {

Object::Object(
    mesh::Mesh mesh,
    const material::Material& material,
    transform::Transform transform
)
    // NOLINTNEXTLINE(performance-move-const-arg)
    : transform{std::move(transform)}
    , mesh{std::move(mesh)}
    , material{material} {}

auto Object::draw(const camera::Camera& camera) const -> void {
    this->material.bind(
        this->transform.get_matrix(),
        camera.get_view_matrix(),
        camera.projection
    );
    this->mesh.draw();
}

} // namespace goon::object
