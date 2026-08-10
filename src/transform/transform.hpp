#pragma once

#include "matrix/matrix.hpp"
#include "quaternion.hpp"

namespace goon::transform {

struct Transform final {
    using Vector = std::array<float, 3>;

    Vector position{0.0f, 0.0f, 0.0f};
    Quaternion rotation{Quaternion::identity()};
    Vector scale{1.0f, 1.0f, 1.0f};

    constexpr Transform() = default;

    constexpr Transform(
        const Vector position, const Quaternion rotation, const Vector scale
    )
        : position{position}
        , rotation{rotation}
        , scale{scale} {
        assert(std::isfinite(rotation.get_w()));
        assert(std::isfinite(rotation.get_x()));
        assert(std::isfinite(rotation.get_y()));
        assert(std::isfinite(rotation.get_z()));
        assert(std::isfinite(position[0]));
        assert(std::isfinite(position[1]));
        assert(std::isfinite(position[2]));
        assert(std::isfinite(scale[0]));
        assert(std::isfinite(scale[1]));
        assert(std::isfinite(scale[2]));
    }

    [[nodiscard]] constexpr auto get_matrix() const
        -> matrix::Matrix<float, 4, 4> {
        const auto w{this->rotation.get_w()};
        const auto x{this->rotation.get_x()};
        const auto y{this->rotation.get_y()};
        const auto z{this->rotation.get_z()};

        const auto xx{2.0f * x * x};
        const auto xy{2.0f * x * y};
        const auto xz{2.0f * x * z};
        const auto xw{2.0f * x * w};
        const auto yy{2.0f * y * y};
        const auto yz{2.0f * y * z};
        const auto yw{2.0f * y * w};
        const auto zz{2.0f * z * z};
        const auto zw{2.0f * z * w};

        // clang-format off
        return matrix::Matrix<float, 4, 4>{std::array{
            (1.0f - yy - zz) * this->scale[0], (xy + zw) * this->scale[0],        (xz - yw) * this->scale[0],        0.0f,
            (xy - zw) * this->scale[1],        (1.0f - xx - zz) * this->scale[1], (yz + xw) * this->scale[1],        0.0f,
            (xz + yw) * this->scale[2],        (yz - xw) * this->scale[2],        (1.0f - xx - yy) * this->scale[2], 0.0f,
            this->position[0],                 this->position[1],                 this->position[2],                 1.0f
        }};
        // clang-format on
    }
};

} // namespace goon::transform
