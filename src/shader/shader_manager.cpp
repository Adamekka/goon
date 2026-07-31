#include "shader_manager.hpp"
#include <algorithm>
#include <fstream>
#include <print>

namespace goon::shader {

namespace {

auto check_shader_compile_status(const uint32_t shader) -> void {
    auto success{int32_t{}};
    auto info_log{std::array<char, 512>{}};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        glGetShaderInfoLog(shader, info_log.size(), nullptr, info_log.data());
        std::println("{}", info_log.data());
    }
}

} // namespace

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

auto ShaderManager::link() -> std::unordered_map<std::string, ShaderArg>& {
    glLinkProgram(this->shader_program);

    check_shader_compile_status(this->shader_program);

    glUseProgram(this->shader_program);

    for (const auto shader : this->shaders) {
        glDeleteShader(shader);
    }

    // Uniforms

    auto uniform_count{int32_t{}};
    auto max_name_length{int32_t{}};

    glGetProgramiv(this->shader_program, GL_ACTIVE_UNIFORMS, &uniform_count);
    glGetProgramiv(
        this->shader_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length
    );

    this->args.clear();
    this->args.reserve(uniform_count);

    auto name{std::vector<char>(max_name_length)};

    for (auto i{0}; i < uniform_count; ++i) {
        auto name_len{int32_t{}};
        auto array_size{int32_t{}};
        auto type{uint32_t{}};

        glGetActiveUniform(
            this->shader_program,
            i,
            max_name_length,
            &name_len,
            &array_size,
            &type,
            name.data()
        );

        auto block_index{int32_t{}};

        // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
        glGetActiveUniformsiv(
            this->shader_program,
            1,
            reinterpret_cast<const uint32_t* const>(&i),
            GL_UNIFORM_BLOCK_INDEX,
            &block_index
        );
        // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

        // Members of named uniform blocks are supplied through UBOs,
        // not through glUniform*.
        if (block_index != -1) {
            continue;
        }

        const auto location{
          glGetUniformLocation(this->shader_program, name.data())
        };

        if (location == -1) {
            // Unexpected for an active default-block uniform.
            assert(false && "Uniform is active but has no location");
            continue;
        }

        this->args.emplace(
            name.data(), ShaderArg{ShaderVarType{type}, location, array_size}
        );
    }

    return this->args;
}

auto ShaderManager::get_args() -> std::unordered_map<std::string, ShaderArg>& {
    return this->args;
}

auto ShaderManager::validate() const -> bool {
    return std::ranges::all_of(
        this->args,
        &ShaderArg::get_data_passed,
        &decltype(this->args)::value_type::second
    );
}

} // namespace goon::shader
