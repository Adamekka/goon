#pragma once

#include "../mesh/vertex.hpp"
#include <vector>

namespace goon::scene::object::importer {

struct ImportedSubmesh final {
    std::vector<mesh::Vertex> vertices;
    size_t material_index;

    constexpr ImportedSubmesh(
        std::vector<mesh::Vertex> vertices, const size_t material_index
    )
        : vertices{std::move(vertices)}
        , material_index{material_index} {}
};

} // namespace goon::scene::object::importer
