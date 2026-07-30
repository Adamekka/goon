#pragma once

#include "shader_var_type.hpp"
#include <array>
#include <cassert>

namespace goon::shader {

template<typename T, size_t Columns, size_t Rows>
    requires(
        std::floating_point<T> && Columns >= 2 && Columns <= 4 && Rows >= 2
        && Rows <= 4
    )
struct ShaderMatrix final {
    // OpenGL consumes this flat storage in column-major order with GL_FALSE.
    std::array<T, Columns * Rows> values;
};

namespace detail {

template<typename T> struct ShaderDataTraits;

// NOLINTBEGIN(bugprone-macro-parentheses)
// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#define GOON_SHADER_SCALAR(TYPE, ENUM, FUNCTION)                               \
    template<> struct ShaderDataTraits<TYPE> final {                           \
        static constexpr auto SHADER_TYPE{ShaderVarType::Value::ENUM};         \
                                                                               \
        static auto pass(const int32_t location, const TYPE data) -> void {    \
            FUNCTION(location, data);                                          \
        }                                                                      \
    };

#define GOON_SHADER_VECTOR(TYPE, SIZE, ENUM, FUNCTION)                         \
    template<> struct ShaderDataTraits<std::array<TYPE, SIZE>> final {         \
        static constexpr auto SHADER_TYPE{ShaderVarType::Value::ENUM};         \
                                                                               \
        static auto                                                            \
        pass(const int32_t location, const std::array<TYPE, SIZE>& data)       \
            -> void {                                                          \
            FUNCTION(location, 1, data.data());                                \
        }                                                                      \
    };

#define GOON_SHADER_MATRIX(TYPE, COLUMNS, ROWS, ENUM, FUNCTION)                \
    template<>                                                                 \
    struct ShaderDataTraits<ShaderMatrix<TYPE, COLUMNS, ROWS>> final {         \
        using Data = ShaderMatrix<TYPE, COLUMNS, ROWS>;                        \
                                                                               \
        static constexpr auto SHADER_TYPE{ShaderVarType::Value::ENUM};         \
        static_assert(sizeof(Data) == sizeof(decltype(Data::values)));         \
                                                                               \
        static auto pass(const int32_t location, const Data& data) -> void {   \
            FUNCTION(location, 1, GL_FALSE, data.values.data());               \
        }                                                                      \
    };

// NOLINTEND(cppcoreguidelines-macro-usage)
// NOLINTEND(bugprone-macro-parentheses)

GOON_SHADER_SCALAR(float, Float, glUniform1f)
GOON_SHADER_VECTOR(float, 2, Vec2, glUniform2fv)
GOON_SHADER_VECTOR(float, 3, Vec3, glUniform3fv)
GOON_SHADER_VECTOR(float, 4, Vec4, glUniform4fv)

GOON_SHADER_MATRIX(float, 2, 2, Mat2, glUniformMatrix2fv)
GOON_SHADER_MATRIX(float, 3, 3, Mat3, glUniformMatrix3fv)
GOON_SHADER_MATRIX(float, 4, 4, Mat4, glUniformMatrix4fv)
GOON_SHADER_MATRIX(float, 2, 3, Mat2x3, glUniformMatrix2x3fv)
GOON_SHADER_MATRIX(float, 2, 4, Mat2x4, glUniformMatrix2x4fv)
GOON_SHADER_MATRIX(float, 3, 2, Mat3x2, glUniformMatrix3x2fv)
GOON_SHADER_MATRIX(float, 3, 4, Mat3x4, glUniformMatrix3x4fv)
GOON_SHADER_MATRIX(float, 4, 2, Mat4x2, glUniformMatrix4x2fv)
GOON_SHADER_MATRIX(float, 4, 3, Mat4x3, glUniformMatrix4x3fv)

GOON_SHADER_SCALAR(int32_t, Int, glUniform1i)
GOON_SHADER_VECTOR(int32_t, 2, IVec2, glUniform2iv)
GOON_SHADER_VECTOR(int32_t, 3, IVec3, glUniform3iv)
GOON_SHADER_VECTOR(int32_t, 4, IVec4, glUniform4iv)

GOON_SHADER_SCALAR(uint32_t, UInt, glUniform1ui)
GOON_SHADER_VECTOR(uint32_t, 2, UVec2, glUniform2uiv)
GOON_SHADER_VECTOR(uint32_t, 3, UVec3, glUniform3uiv)
GOON_SHADER_VECTOR(uint32_t, 4, UVec4, glUniform4uiv)

GOON_SHADER_SCALAR(double, Double, glUniform1d)
GOON_SHADER_VECTOR(double, 2, DVec2, glUniform2dv)
GOON_SHADER_VECTOR(double, 3, DVec3, glUniform3dv)
GOON_SHADER_VECTOR(double, 4, DVec4, glUniform4dv)

GOON_SHADER_MATRIX(double, 2, 2, DMat2, glUniformMatrix2dv)
GOON_SHADER_MATRIX(double, 3, 3, DMat3, glUniformMatrix3dv)
GOON_SHADER_MATRIX(double, 4, 4, DMat4, glUniformMatrix4dv)
GOON_SHADER_MATRIX(double, 2, 3, DMat2x3, glUniformMatrix2x3dv)
GOON_SHADER_MATRIX(double, 2, 4, DMat2x4, glUniformMatrix2x4dv)
GOON_SHADER_MATRIX(double, 3, 2, DMat3x2, glUniformMatrix3x2dv)
GOON_SHADER_MATRIX(double, 3, 4, DMat3x4, glUniformMatrix3x4dv)
GOON_SHADER_MATRIX(double, 4, 2, DMat4x2, glUniformMatrix4x2dv)
GOON_SHADER_MATRIX(double, 4, 3, DMat4x3, glUniformMatrix4x3dv)

#undef GOON_SHADER_MATRIX
#undef GOON_SHADER_SCALAR
#undef GOON_SHADER_VECTOR

template<typename T>
concept ShaderData = requires(const int32_t location, const T& data) {
    ShaderDataTraits<T>::SHADER_TYPE;
    ShaderDataTraits<T>::pass(location, data);
};

} // namespace detail

class ShaderArg final {
  public:
    constexpr ShaderArg(
        ShaderVarType type, int32_t location, int32_t array_size
    )
        : type{type}
        , location{location}
        , array_size{array_size} {}

    ShaderArg(const ShaderArg&) = delete;
    ShaderArg(ShaderArg&&) = default;

    ~ShaderArg() = default;

    auto operator=(const ShaderArg&) -> ShaderArg& = delete;
    auto operator=(ShaderArg&&) -> ShaderArg& = default;

    template<detail::ShaderData T> auto pass_data(const T& data) -> void {
        assert(this->type.value == detail::ShaderDataTraits<T>::SHADER_TYPE);
        detail::ShaderDataTraits<T>::pass(this->location, data);
        this->data_passed = true;
    }

    [[nodiscard]] constexpr auto get_type() const -> ShaderVarType {
        return this->type;
    }

    [[nodiscard]] constexpr auto get_location() const -> int32_t {
        return this->location;
    }

    [[nodiscard]] constexpr auto get_array_size() const -> int32_t {
        return this->array_size;
    }

    [[nodiscard]] constexpr auto get_data_passed() const -> bool {
        return this->data_passed;
    }

  private:
    ShaderVarType type;
    int32_t location;
    int32_t array_size;

    bool data_passed{false};
};

} // namespace goon::shader
