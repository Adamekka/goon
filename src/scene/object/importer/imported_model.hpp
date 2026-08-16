#pragma once

#include "imported_material.hpp"
#include "imported_submesh.hpp"
#include "imported_texture.hpp"

namespace goon::scene::object::importer {

struct ImportedModel final {
    std::vector<ImportedTexture> textures;
    std::vector<ImportedMaterial> materials;
    std::vector<ImportedSubmesh> submeshes;

    constexpr ImportedModel(
        std::vector<ImportedTexture> textures,
        std::vector<ImportedMaterial> materials,
        std::vector<ImportedSubmesh> submeshes
    )
        : textures{std::move(textures)}
        , materials{std::move(materials)}
        , submeshes{std::move(submeshes)} {}
};

} // namespace goon::scene::object::importer
