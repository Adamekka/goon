#pragma once

#include <array>
#include <cassert>
#include <cmath>

namespace goon::transform {

class Quaternion final {
  public:
    constexpr Quaternion(
        const float w, const float x, const float y, const float z
    )
        : w{w}
        , x{x}
        , y{y}
        , z{z} {
        const auto length{std::hypot(
            std::hypot(this->w, this->x), std::hypot(this->y, this->z)
        )};
        assert(std::isfinite(length) && length > 0.0f);

        this->w /= length;
        this->x /= length;
        this->y /= length;
        this->z /= length;
    }

    [[nodiscard]] static consteval auto identity() -> Quaternion {
        return Quaternion{AlreadyNormalized{}, 1.0f, 0.0f, 0.0f, 0.0f};
    }

    [[nodiscard]] static constexpr auto
    from_axis_angle(const float radians, const std::array<float, 3>& axis)
        -> Quaternion {
        assert(std::isfinite(radians));
        const auto axis_length{std::hypot(axis[0], axis[1], axis[2])};
        assert(std::isfinite(axis_length) && axis_length > 0.0f);

        const auto half_radians{radians / 2.0f};
        const auto scale{std::sin(half_radians) / axis_length};
        return Quaternion{
            std::cos(half_radians),
            axis[0] * scale,
            axis[1] * scale,
            axis[2] * scale
        };
    }

    [[nodiscard]] constexpr auto get_w() const -> float {
        return this->w;
    }

    [[nodiscard]] constexpr auto get_x() const -> float {
        return this->x;
    }

    [[nodiscard]] constexpr auto get_y() const -> float {
        return this->y;
    }

    [[nodiscard]] constexpr auto get_z() const -> float {
        return this->z;
    }

    [[nodiscard]] constexpr auto conjugate() const -> Quaternion {
        return Quaternion{
            AlreadyNormalized{}, this->w, -this->x, -this->y, -this->z
        };
    }

    // NOLINTBEGIN(fuchsia-overloaded-operator)

    [[nodiscard]] friend auto
    operator*(const Quaternion left, const Quaternion right) -> Quaternion {
        return Quaternion{
            (left.w * right.w) - (left.x * right.x) - (left.y * right.y)
                - (left.z * right.z),
            (left.w * right.x) + (left.x * right.w) + (left.y * right.z)
                - (left.z * right.y),
            (left.w * right.y) - (left.x * right.z) + (left.y * right.w)
                + (left.z * right.x),
            (left.w * right.z) + (left.x * right.y) - (left.y * right.x)
                + (left.z * right.w)
        };
    }

    // NOLINTEND(fuchsia-overloaded-operator)

  private:
    struct AlreadyNormalized final {};

    float w;
    float x;
    float y;
    float z;

    constexpr Quaternion(
        const AlreadyNormalized /* unused */,
        const float w,
        const float x,
        const float y,
        const float z
    )
        : w{w}
        , x{x}
        , y{y}
        , z{z} {}
};

} // namespace goon::transform
