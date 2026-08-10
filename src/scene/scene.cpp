#include "scene.hpp"

namespace goon::scene {

auto Scene::update() const -> void {
    for (const auto& object : this->objects) {
        object.draw(this->camera, this->light);
    }
}

auto Scene::create_object(
    object::mesh::Mesh mesh,
    const object::material::Material& material,
    const transform::Transform transform
) -> object::Object* {
    this->objects.emplace_back(std::move(mesh), material, transform);
    return &this->objects.back();
}

} // namespace goon::scene
