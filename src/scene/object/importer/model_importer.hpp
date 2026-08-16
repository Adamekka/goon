#pragma once

#include "imported_model.hpp"
#include <expected>
#include <filesystem>

namespace goon::scene::object::importer {

class ModelImporter final {
  public:
    ModelImporter() = delete;

    ModelImporter(const ModelImporter&) = delete;
    ModelImporter(ModelImporter&&) = delete;

    auto operator=(const ModelImporter&) -> ModelImporter& = delete;
    auto operator=(ModelImporter&&) -> ModelImporter& = delete;

    ~ModelImporter() = delete;

    [[nodiscard]] static auto import(const std::filesystem::path& path)
        -> std::expected<ImportedModel, std::string>;
};

} // namespace goon::scene::object::importer
