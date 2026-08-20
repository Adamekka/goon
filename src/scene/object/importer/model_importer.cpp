#include "model_importer.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
auto goon::scene::object::importer::ModelImporter::import(
    const std::filesystem::path& path
) -> std::expected<ImportedModel, std::string> {
    auto importer{Assimp::Importer{}};

    const auto failure{
        [&path](std::string_view detail) -> std::unexpected<std::string> {
            auto message{std::string{"Failed to import model '"}};
            message.append(path.string()).append("': ").append(detail);
            return std::unexpected{std::move(message)};
        }
    };

    const auto import_flags{
        aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals
        | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes
        | aiProcess_Triangulate
    };

    const auto* const ai_scene{importer.ReadFile(path.c_str(), import_flags)};

    if (ai_scene == nullptr) {
        return failure(importer.GetErrorString());
    }

    if (ai_scene->mRootNode == nullptr) {
        return failure("model has no root node");
    }

    if (ai_scene->mNumMeshes == 0) {
        return failure("model has no meshes");
    }

    auto textures{std::vector<ImportedTexture>{}};
    textures.reserve(ai_scene->mNumTextures);

    for (auto texture_index{size_t{0}}; texture_index < ai_scene->mNumTextures;
         ++texture_index) {
        const auto* const texture{ai_scene->mTextures[texture_index]};

        if (texture == nullptr || texture->pcData == nullptr
            || texture->mWidth == 0) {
            return failure(
                "embedded texture " + std::to_string(texture_index)
                + " has no data"
            );
        }

        // Embedded glTF images are encoded PNG or JPEG byte streams.
        if (texture->mHeight != 0) {
            return failure(
                "embedded texture " + std::to_string(texture_index)
                + " is not encoded PNG or JPEG data"
            );
        }

        const auto* const begin{
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            reinterpret_cast<const uint8_t*>(texture->pcData)
        };
        const auto* const end{begin + texture->mWidth};

        textures.emplace_back(std::vector<uint8_t>{begin, end});
    }

    auto materials{std::vector<ImportedMaterial>{}};
    materials.reserve(ai_scene->mNumMaterials);

    constexpr auto UNIMPORTED_MATERIAL{std::numeric_limits<size_t>::max()};
    auto material_indices{
        std::vector<size_t>(ai_scene->mNumMaterials, UNIMPORTED_MATERIAL)
    };

    auto submeshes{std::vector<ImportedSubmesh>{}};
    submeshes.reserve(ai_scene->mNumMeshes);

    for (auto mesh_index{size_t{0}}; mesh_index < ai_scene->mNumMeshes;
         ++mesh_index) {
        const auto* const mesh{ai_scene->mMeshes[mesh_index]};

        if (mesh == nullptr) {
            return failure(
                "mesh " + std::to_string(mesh_index) + " is missing"
            );
        }

        if (mesh->mVertices == nullptr || mesh->mNormals == nullptr) {
            return failure(
                "mesh " + std::to_string(mesh_index)
                + " has no vertices or normals"
            );
        }

        if (mesh->mMaterialIndex >= ai_scene->mNumMaterials) {
            return failure(
                "mesh " + std::to_string(mesh_index)
                + " references an invalid material"
            );
        }

        auto& material_index{material_indices[mesh->mMaterialIndex]};

        if (material_index == UNIMPORTED_MATERIAL) {
            const auto* const material{
                ai_scene->mMaterials[mesh->mMaterialIndex]
            };

            if (material == nullptr) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " is missing"
                );
            }

            auto texture_path{aiString{}};
            const auto result{
                material->GetTexture(aiTextureType_BASE_COLOR, 0, &texture_path)
            };

            if (result != AI_SUCCESS) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " has no base-color texture"
                );
            }

            const auto [texture, texture_index]{
                ai_scene->GetEmbeddedTextureAndIndex(texture_path.C_Str())
            };

            if (texture == nullptr || texture_index < 0) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " does not reference an embedded texture"
                );
            }

            if (static_cast<size_t>(texture_index) >= textures.size()) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " references an invalid embedded texture"
                );
            }

            auto shininess{float{}};
            if (material->Get(AI_MATKEY_SHININESS, shininess) != AI_SUCCESS) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " has no shininess value"
                );
            }
            if (!std::isfinite(shininess) || shininess < 0.0f) {
                return failure(
                    "material " + std::to_string(mesh->mMaterialIndex)
                    + " has invalid shininess"
                );
            }

            material_index = materials.size();
            materials.emplace_back(
                static_cast<size_t>(texture_index), shininess
            );
        }

        auto vertices{std::vector<mesh::Vertex>{}};
        vertices.reserve(static_cast<size_t>(mesh->mNumFaces) * 3);

        for (auto face_index{size_t{0}}; face_index < mesh->mNumFaces;
             ++face_index) {
            const auto& face{mesh->mFaces[face_index]};

            if (face.mNumIndices != 3 || face.mIndices == nullptr) {
                return failure(
                    "mesh " + std::to_string(mesh_index)
                    + " contains a non-triangle face"
                );
            }

            for (auto index_index{size_t{0}}; index_index < face.mNumIndices;
                 ++index_index) {
                const auto vertex_index{face.mIndices[index_index]};

                if (vertex_index >= mesh->mNumVertices) {
                    return failure(
                        "mesh " + std::to_string(mesh_index)
                        + " contains an invalid vertex index"
                    );
                }

                vertices.emplace_back(
                    mesh::Position{
                        mesh->mVertices[vertex_index].x,
                        mesh->mVertices[vertex_index].y,
                        mesh->mVertices[vertex_index].z
                    },
                    mesh->mColors[0] != nullptr
                        ? mesh::Color{
                              mesh->mColors[0][vertex_index].r,
                              mesh->mColors[0][vertex_index].g,
                              mesh->mColors[0][vertex_index].b,
                              mesh->mColors[0][vertex_index].a
                          }
                        : mesh::Color{},
                    mesh->mTextureCoords[0] != nullptr
                        ? mesh::TextureCoordinates{
                              mesh->mTextureCoords[0][vertex_index].x,
                              mesh->mTextureCoords[0][vertex_index].y
                          }
                        : mesh::TextureCoordinates{},
                    mesh::NormalVector{
                        mesh->mNormals[vertex_index].x,
                        mesh->mNormals[vertex_index].y,
                        mesh->mNormals[vertex_index].z
                    }
                );
            }
        }

        submeshes.emplace_back(std::move(vertices), material_index);
    }

    return ImportedModel{
        std::move(textures), std::move(materials), std::move(submeshes)
    };
}
