#pragma once

#include <vector>

namespace goon::scene::object::importer {

struct ImportedTexture final {
    std::vector<uint8_t> data;

    constexpr explicit ImportedTexture(std::vector<uint8_t> data)
        : data{std::move(data)} {}
};

} // namespace goon::scene::object::importer
