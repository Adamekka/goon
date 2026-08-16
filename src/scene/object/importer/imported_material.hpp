#pragma once

#include <cstddef>

namespace goon::scene::object::importer {

struct ImportedMaterial final {
    size_t base_color_texture_index;

    explicit constexpr ImportedMaterial(const size_t base_color_texture_index)
        : base_color_texture_index{base_color_texture_index} {}
};

} // namespace goon::scene::object::importer
