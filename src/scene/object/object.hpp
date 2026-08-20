#pragma once

#include "../camera/camera.hpp"
#include "material/material.hpp"
#include "mesh/mesh.hpp"

namespace goon::scene {
class Scene;
} // namespace goon::scene

namespace goon::scene::object {

class Object final {
  public:
    transform::Transform transform;

    Object(const Object&) = delete;
    Object(Object&&) = default;

    ~Object() = default;

    auto operator=(const Object&) -> Object& = delete;
    auto operator=(Object&&) -> Object& = default;

    auto draw(const camera::Camera& camera, const light::Light& light) const
        -> void;

  private:
    friend class scene::Scene;

    struct Submesh final {
        mesh::Mesh mesh;
        const material::Material* material;

        Submesh(mesh::Mesh mesh, const material::Material& material)
            : mesh{std::move(mesh)}
            , material{&material} {}
    };

    // Finalize these before submeshes capture pointers; moving their vectors
    // preserves element addresses, but later reallocation would not.
    std::vector<material::texture::Texture> textures;
    std::vector<material::Material> materials;
    std::vector<Submesh> submeshes;

    Object(
        mesh::Mesh mesh,
        const material::Material& material,
        transform::Transform transform
    );

    Object(
        std::vector<material::texture::Texture> textures,
        std::vector<material::Material> materials,
        std::vector<Submesh> submeshes,
        transform::Transform transform
    );

    [[nodiscard]] static auto load(
        const std::filesystem::path& path,
        material::shader::ShaderProgram& shader_program,
        transform::Transform transform
    ) -> std::expected<Object, std::string>;
};

} // namespace goon::scene::object
