#pragma once

#include "shader_arg.hpp"
#include "shader_type.hpp"
#include <filesystem>
#include <unordered_map>
#include <vector>

namespace goon::object::material::shader {

class ShaderProgram final {
  public:
    ShaderProgram() = default;

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;

    ~ShaderProgram();

    auto operator=(const ShaderProgram&) -> ShaderProgram& = delete;
    auto operator=(ShaderProgram&&) -> ShaderProgram& = delete;

    auto compile(const std::filesystem::path& path, ShaderType type) -> void;

    [[nodiscard]] auto link() -> std::unordered_map<std::string, ShaderArg>&;

    auto bind() const -> void;

    static auto unbind() -> void;

    [[nodiscard]] auto get_args()
        -> std::unordered_map<std::string, ShaderArg>&;

  private:
    const uint32_t id{glCreateProgram()};
    std::vector<uint32_t> shaders;

    std::unordered_map<std::string, ShaderArg> args;
};

} // namespace goon::object::material::shader
