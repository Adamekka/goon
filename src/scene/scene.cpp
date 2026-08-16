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
    return &*this->objects.emplace(std::move(mesh), material, transform);
}

auto Scene::create_object(
    const std::filesystem::path& path,
    object::material::shader::ShaderProgram& shader_program,
    const transform::Transform transform
) -> std::expected<object::Object*, std::string> {
    auto object_result{object::Object::load(path, shader_program, transform)};

    if (!object_result.has_value()) {
        return std::unexpected{std::move(object_result.error())};
    }

    return &*this->objects.emplace(std::move(*object_result));
}

} // namespace goon::scene
