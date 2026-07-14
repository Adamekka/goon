#pragma once

#include "shader_type.hpp"
#include <filesystem>
#include <vector>

namespace goon::shader {

class ShaderManager final {
  public:
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager(ShaderManager&&) = delete;

    auto operator=(const ShaderManager&) -> ShaderManager& = delete;
    auto operator=(ShaderManager&&) -> ShaderManager& = delete;

    static auto instance() -> ShaderManager&;

    auto compile(const std::filesystem::path& path, ShaderType type) -> void;

    auto link() const -> void;

  private:
    const uint32_t shader_program;
    std::vector<uint32_t> shaders;

    ShaderManager();

    ~ShaderManager() = default;
};

} // namespace goon::shader
