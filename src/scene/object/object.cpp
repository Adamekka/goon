#include "object.hpp"

namespace goon::scene::object {

Object::Object(
    mesh::Mesh mesh,
    const material::Material& material,
    transform::Transform transform
)
    : transform{transform}
    , mesh{std::move(mesh)}
    , material{&material} {}

auto Object::draw(const camera::Camera& camera, const light::Light& light) const
    -> void {
    this->material->bind(
        this->transform.get_matrix(),
        camera.get_view_matrix(),
        camera.projection,
        light
    );
    this->mesh.draw();
}

} // namespace goon::scene::object
