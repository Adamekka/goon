#pragma once

#include <array>

namespace goon::shader {

template<typename T, size_t Columns, size_t Rows>
    requires(
        Columns >= 2 && Columns <= 4 && Rows >= 2 && Rows <= 4
        && (std::same_as<T, float> || std::same_as<T, double>)
    )
class Matrix final {
  public:
    // OpenGL consumes this flat storage in column-major order with GL_FALSE.
    std::array<T, Columns * Rows> values;

    constexpr Matrix() = default;

    constexpr explicit Matrix(std::array<T, Columns * Rows> values)
        : values{std::move(values)} {}

    constexpr explicit Matrix(
        const std::array<std::array<T, Rows>, Columns>& values
    )
        : values{[&values]() -> auto {
            auto flat{std::array<T, Columns * Rows>{}};
            for (size_t column{0}; column < Columns; ++column) {
                for (size_t row{0}; row < Rows; ++row) {
                    flat[(column * Rows) + row] = values[column][row];
                }
            }
            return flat;
        }()} {}

    constexpr Matrix(const Matrix&) = default;
    constexpr Matrix(Matrix&&) = default;

    ~Matrix() = default;

    constexpr auto operator=(const Matrix&) -> Matrix& = default;
    constexpr auto operator=(Matrix&&) -> Matrix& = default;

    template<size_t Column, size_t Row>
    [[nodiscard]] constexpr auto get() -> T& {
        static_assert(Column < Columns, "Matrix column index is out of bounds");
        static_assert(Row < Rows, "Matrix row index is out of bounds");
        return this->values[(Column * Rows) + Row];
    }

    template<size_t Column, size_t Row>
    [[nodiscard]] constexpr auto get() const -> const T& {
        static_assert(Column < Columns, "Matrix column index is out of bounds");
        static_assert(Row < Rows, "Matrix row index is out of bounds");
        return this->values[(Column * Rows) + Row];
    }
};

} // namespace goon::shader
