#pragma once

#include "shader_arg.hpp"
#include "shader_type.hpp"
#include <filesystem>
#include <unordered_map>
#include <vector>

namespace goon::shader {

class ShaderManager final {
  public:
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager(ShaderManager&&) = delete;

    auto operator=(const ShaderManager&) -> ShaderManager& = delete;
    auto operator=(ShaderManager&&) -> ShaderManager& = delete;

    [[nodiscard]] static auto instance() -> ShaderManager&;

    auto compile(const std::filesystem::path& path, ShaderType type) -> void;

    [[nodiscard]] auto link() -> std::unordered_map<std::string, ShaderArg>&;

    [[nodiscard]] auto get_args()
        -> std::unordered_map<std::string, ShaderArg>&;

    [[nodiscard]] auto validate() const -> bool;

  private:
    const uint32_t shader_program{glCreateProgram()};
    std::vector<uint32_t> shaders;

    std::unordered_map<std::string, ShaderArg> args;

    ShaderManager() = default;

    ~ShaderManager() = default;
};

} // namespace goon::shader
