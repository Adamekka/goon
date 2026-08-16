#include "object.hpp"
#include "importer/model_importer.hpp"

namespace goon::scene::object {

Object::Object(
    mesh::Mesh mesh,
    const material::Material& material,
    const transform::Transform transform
)
    : transform{transform} {
    this->submeshes.emplace_back(std::move(mesh), material);
}

auto Object::draw(const camera::Camera& camera, const light::Light& light) const
    -> void {
    const auto model_matrix{this->transform.get_matrix()};
    const auto normal_matrix{this->transform.get_normal_matrix()};
    const auto view_matrix{camera.get_view_matrix()};

    for (const auto& submesh : this->submeshes) {
        submesh.material->bind(
            model_matrix, normal_matrix, view_matrix, camera.projection, light
        );
        submesh.mesh.draw();
    }
}

Object::Object(
    std::vector<material::texture::Texture> textures,
    std::vector<material::Material> materials,
    std::vector<Submesh> submeshes,
    const transform::Transform transform
)
    : transform{transform}
    , textures{std::move(textures)}
    , materials{std::move(materials)}
    , submeshes{std::move(submeshes)} {}

auto Object::load(
    const std::filesystem::path& path,
    material::shader::ShaderProgram& shader_program,
    const transform::Transform transform
) -> std::expected<Object, std::string> {
    auto imported_model_result{importer::ModelImporter::import(path)};

    if (!imported_model_result.has_value()) {
        return std::unexpected{std::move(imported_model_result.error())};
    }

    auto imported_model{std::move(*imported_model_result)};
    auto textures{std::vector<material::texture::Texture>{}};
    textures.reserve(imported_model.textures.size());

    for (auto texture_index{size_t{0}};
         texture_index < imported_model.textures.size();
         ++texture_index) {
        auto texture_result{material::texture::Texture::load(
            imported_model.textures[texture_index].data
        )};

        if (!texture_result.has_value()) {
            auto message{std::string{"Failed to load texture "}};
            message.append(std::to_string(texture_index))
                .append(" from model '")
                .append(path.string())
                .append("': ")
                .append(texture_result.error());
            return std::unexpected{std::move(message)};
        }

        textures.emplace_back(std::move(*texture_result));
    }

    auto materials{std::vector<material::Material>{}};
    materials.reserve(imported_model.materials.size());

    for (auto material_index{size_t{0}};
         material_index < imported_model.materials.size();
         ++material_index) {
        const auto texture_index{
            imported_model.materials[material_index].base_color_texture_index
        };

        if (texture_index >= textures.size()) {
            return std::unexpected{
                "Material " + std::to_string(material_index) + " in model '"
                + path.string() + "' references an invalid texture"
            };
        }

        materials.emplace_back(shader_program, textures[texture_index]);
    }

    auto submeshes{std::vector<Submesh>{}};
    submeshes.reserve(imported_model.submeshes.size());

    for (auto submesh_index{size_t{0}};
         submesh_index < imported_model.submeshes.size();
         ++submesh_index) {
        auto& imported_submesh{imported_model.submeshes[submesh_index]};

        if (imported_submesh.material_index >= materials.size()) {
            return std::unexpected{
                "Submesh " + std::to_string(submesh_index) + " in model '"
                + path.string() + "' references an invalid material"
            };
        }

        submeshes.emplace_back(
            mesh::Mesh{
                std::move(imported_submesh.vertices),
                mesh::MeshDrawMode{mesh::MeshDrawMode::Value::Triangles}
            },
            materials[imported_submesh.material_index]
        );
    }

    return Object{
        std::move(textures),
        std::move(materials),
        std::move(submeshes),
        transform
    };
}

} // namespace goon::scene::object
