#pragma once

#include <array>
#include <print>

namespace goon::shader {

template<typename T, size_t Columns, size_t Rows>
    requires(
        Columns >= 2 && Columns <= 4 && Rows >= 2 && Rows <= 4
        && (std::same_as<T, float> || std::same_as<T, double>)
    )
class Matrix final {
  public:
    // MARK: Lifecycle

    // OpenGL consumes this flat storage in column-major order with GL_FALSE.
    std::array<T, Columns * Rows> values;

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

    // MARK: Factory methods

    [[nodiscard]] static consteval auto zero() -> Matrix {
        return Matrix{std::array<T, Columns * Rows>{}};
    }

    [[nodiscard]] static consteval auto identity() -> Matrix {
        auto values{std::array<T, Columns * Rows>{}};
        for (size_t column{0}; column < Columns; ++column) {
            for (size_t row{0}; row < Rows; ++row) {
                values[(column * Rows) + row] = (column == row) ? 1 : 0;
            }
        }
        return Matrix{values};
    }

    // MARK: Getters

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

    // MARK: Multiplication

    // NOLINTBEGIN(fuchsia-overloaded-operator)

    template<size_t RightColumns>
    [[nodiscard]] constexpr auto
    operator*(const Matrix<T, RightColumns, Columns>& right) const
        -> Matrix<T, RightColumns, Rows> {
        auto result{Matrix<T, RightColumns, Rows>::zero()};
        for (size_t column{0}; column < RightColumns; ++column) {
            for (size_t row{0}; row < Rows; ++row) {
                for (size_t shared{0}; shared < Columns; ++shared) {
                    result.values[(column * Rows) + row]
                        += this->values[(shared * Rows) + row]
                         * right.values[(column * Columns) + shared];
                }
            }
        }
        return result;
    }

    [[nodiscard]] constexpr auto
    operator*(const std::array<T, Columns>& vector) const
        -> std::array<T, Rows> {
        auto result{std::array<T, Rows>{}};
        for (size_t row{0}; row < Rows; ++row) {
            for (size_t column{0}; column < Columns; ++column) {
                result[row]
                    += this->values[(column * Rows) + row] * vector[column];
            }
        }
        return result;
    }

    [[nodiscard]] constexpr auto operator*(const T scalar) const -> Matrix {
        auto result{*this};
        result *= scalar;
        return result;
    }

    constexpr auto operator*=(const Matrix<T, Columns, Columns>& right)
        -> Matrix& {
        *this = *this * right;
        return *this;
    }

    constexpr auto operator*=(const T scalar) -> Matrix& {
        for (auto& value : this->values) {
            value *= scalar;
        }
        return *this;
    }

    [[nodiscard]] friend constexpr auto
    operator*(const std::array<T, Rows>& vector, const Matrix& matrix)
        -> std::array<T, Columns> {
        auto result{std::array<T, Columns>{}};
        for (size_t column{0}; column < Columns; ++column) {
            for (size_t row{0}; row < Rows; ++row) {
                result[column]
                    += vector[row] * matrix.values[(column * Rows) + row];
            }
        }
        return result;
    }

    [[nodiscard]] friend constexpr auto
    operator*(const T scalar, const Matrix& matrix) -> Matrix {
        return matrix * scalar;
    }

    // NOLINTEND(fuchsia-overloaded-operator)

    // MARK: Transformations

    constexpr auto scale(const std::array<T, Rows - 1>& factors) -> void
        requires(Columns == Rows && (Rows == 3 || Rows == 4))
    {
        for (size_t column{0}; column < Columns - 1; ++column) {
            for (size_t row{0}; row < Rows; ++row) {
                this->values[(column * Rows) + row] *= factors[column];
            }
        }
    }

    constexpr auto rotate(const T radians) -> void
        requires(Columns == 3 && Rows == 3)
    {
        const auto cosine{std::cos(radians)};
        const auto sine{std::sin(radians)};
        for (size_t row{0}; row < Rows; ++row) {
            const auto x{this->values[row]};
            const auto y{this->values[Rows + row]};
            this->values[row] = (x * cosine) + (y * sine);
            this->values[Rows + row] = (y * cosine) - (x * sine);
        }
    }

    constexpr auto rotate_x(const T radians) -> void
        requires(Columns == 4 && Rows == 4)
    {
        const auto cosine{std::cos(radians)};
        const auto sine{std::sin(radians)};
        for (size_t row{0}; row < Rows; ++row) {
            const auto y{this->values[Rows + row]};
            const auto z{this->values[(2 * Rows) + row]};
            this->values[Rows + row] = (y * cosine) + (z * sine);
            this->values[(2 * Rows) + row] = (z * cosine) - (y * sine);
        }
    }

    constexpr auto rotate_y(const T radians) -> void
        requires(Columns == 4 && Rows == 4)
    {
        const auto cosine{std::cos(radians)};
        const auto sine{std::sin(radians)};
        for (size_t row{0}; row < Rows; ++row) {
            const auto x{this->values[row]};
            const auto z{this->values[(2 * Rows) + row]};
            this->values[row] = (x * cosine) - (z * sine);
            this->values[(2 * Rows) + row] = (x * sine) + (z * cosine);
        }
    }

    constexpr auto rotate_z(const T radians) -> void
        requires(Columns == 4 && Rows == 4)
    {
        const auto cosine{std::cos(radians)};
        const auto sine{std::sin(radians)};
        for (size_t row{0}; row < Rows; ++row) {
            const auto x{this->values[row]};
            const auto y{this->values[Rows + row]};
            this->values[row] = (x * cosine) + (y * sine);
            this->values[Rows + row] = (y * cosine) - (x * sine);
        }
    }

    constexpr auto translate(const std::array<T, Rows - 1>& offset) -> void
        requires(Columns == Rows && (Rows == 3 || Rows == 4))
    {
        for (size_t row{0}; row < Rows; ++row) {
            auto& translated_value{this->values[((Columns - 1) * Rows) + row]};
            for (size_t column{0}; column < Columns - 1; ++column) {
                translated_value
                    += this->values[(column * Rows) + row] * offset[column];
            }
        }
    }

    // MARK: String conversion

    [[nodiscard]] auto to_string() const -> std::string {
        auto result{std::format(
            "{}mat{}x{}(\n", std::same_as<T, double> ? "d" : "", Columns, Rows
        )};
        for (size_t column{0}; column < Columns; ++column) {
            result += "    (";
            for (size_t row{0}; row < Rows; ++row) {
                result += std::format(
                    "{}{:f}",
                    row == 0 ? "" : ", ",
                    this->values[(column * Rows) + row]
                );
            }
            result += column == Columns - 1 ? ")\n" : "),\n";
        }
        result += ')';
        return result;
    }

    auto print() const -> void {
        std::println("{}", this->to_string());
    }
};

} // namespace goon::shader
