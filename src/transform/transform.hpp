#pragma once

#include "goon/math/matrix.hpp"
#include "position.hpp"
#include "quaternion.hpp"
#include "scale.hpp"

namespace goon::transform {

struct Transform final {
    Position position;
    Quaternion rotation{Quaternion::identity()};
    Scale scale;

    constexpr Transform() = default;

    constexpr Transform(
        const Position position, const Quaternion rotation, const Scale scale
    )
        : position{position}
        , rotation{rotation}
        , scale{scale} {}

    [[nodiscard]] constexpr auto get_matrix() const
        -> math::Matrix<float, 4, 4> {
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
        return math::Matrix<float, 4, 4>{std::array{
            (1.0f - yy - zz) * this->scale.x, (xy + zw) * this->scale.x,        (xz - yw) * this->scale.x,        0.0f,
            (xy - zw) * this->scale.y,        (1.0f - xx - zz) * this->scale.y, (yz + xw) * this->scale.y,        0.0f,
            (xz + yw) * this->scale.z,        (yz - xw) * this->scale.z,        (1.0f - xx - yy) * this->scale.z, 0.0f,
            this->position.x,                 this->position.y,                 this->position.z,                 1.0f
        }};
        // clang-format on
    }

    [[nodiscard]] constexpr auto get_normal_matrix() const
        -> math::Matrix<float, 3, 3> {
        core::assert_ne(this->scale.x, 0.0f);
        core::assert_ne(this->scale.y, 0.0f);
        core::assert_ne(this->scale.z, 0.0f);

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
        return math::Matrix<float, 3, 3>{std::array{
            (1.0f - yy - zz) / this->scale.x, (xy + zw) / this->scale.x,        (xz - yw) / this->scale.x,
            (xy - zw) / this->scale.y,        (1.0f - xx - zz) / this->scale.y, (yz + xw) / this->scale.y,
            (xz + yw) / this->scale.z,        (yz - xw) / this->scale.z,        (1.0f - xx - yy) / this->scale.z
        }};
        // clang-format on
    }
};

} // namespace goon::transform
