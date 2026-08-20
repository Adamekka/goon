#pragma once

#include <cstddef>

namespace goon::scene::object::importer {

struct ImportedMaterial final {
    size_t base_color_texture_index;
    float shininess;

    constexpr ImportedMaterial(
        const size_t base_color_texture_index, const float shininess
    )
        : base_color_texture_index{base_color_texture_index}
        , shininess{shininess} {}
};

} // namespace goon::scene::object::importer
