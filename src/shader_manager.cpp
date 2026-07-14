#include "shader_manager.hpp"
#include <fstream>
#include <print>

namespace goon {

namespace {

auto check_shader_compile_status(const uint32_t shader) -> void {
    auto success{int32_t{0}};
    auto info_log{std::array<char, 512>{}};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, info_log.data());
        std::println("{}", info_log.data());
    }
}

} // namespace

ShaderManager::ShaderManager()
    : shader_program{glCreateProgram()} {}

auto ShaderManager::instance() -> ShaderManager& {
    static auto instance{ShaderManager{}};
    return instance;
}

auto ShaderManager::compile(
    const std::filesystem::path& path, const ShaderType type
) -> void {
    auto shader_source_stream{std::ifstream{path}};
    const auto source{std::string{
      std::istreambuf_iterator<char>{shader_source_stream},
      std::istreambuf_iterator<char>{}
    }};

    const auto shader{glCreateShader(type.get())};
    const auto* const source_ptr{source.c_str()};
    glShaderSource(shader, 1, &source_ptr, nullptr);

    glCompileShader(shader);

    check_shader_compile_status(shader);

    this->shaders.emplace_back(shader);
    glAttachShader(this->shader_program, shader);
}

auto ShaderManager::link() const -> void {
    glLinkProgram(this->shader_program);

    check_shader_compile_status(this->shader_program);

    glUseProgram(this->shader_program);

    for (const auto shader : this->shaders) {
        glDeleteShader(shader);
    }
}

} // namespace goon
