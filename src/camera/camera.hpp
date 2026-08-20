#pragma once

#include "transform/transform.hpp"

namespace goon::scene {
class Scene;
} // namespace goon::scene

namespace goon::camera {

class Camera final {
  public:
    float fov_radians;
    float aspect_ratio;
    float z_near;
    float z_far;

    transform::Transform transform;
    math::Matrix<float, 4, 4> projection;

    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;

    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = default;

    constexpr auto look_at(transform::Position target) -> void {
        this->look_at(this->transform.position, target);
    }

    constexpr auto look_at(
        transform::Position eye,
        transform::Position center,
        transform::Position up = {0.0f, 1.0f, 0.0f}
    ) -> void {
        const auto view{math::Matrix<float, 4, 4>::look_at(
            eye.to_array(), center.to_array(), up.to_array()
        )};

        const auto r00{view.get<0, 0>()};
        const auto r01{view.get<0, 1>()};
        const auto r02{view.get<0, 2>()};
        const auto r10{view.get<1, 0>()};
        const auto r11{view.get<1, 1>()};
        const auto r12{view.get<1, 2>()};
        const auto r20{view.get<2, 0>()};
        const auto r21{view.get<2, 1>()};
        const auto r22{view.get<2, 2>()};

        const auto rotation{[&]() -> transform::Quaternion {
            const auto trace{r00 + r11 + r22};
            if (trace > 0.0f) {
                const auto scale{2.0f * std::sqrt(trace + 1.0f)};
                return transform::Quaternion{
                    0.25f * scale,
                    (r21 - r12) / scale,
                    (r02 - r20) / scale,
                    (r10 - r01) / scale
                };
            }

            if (r00 > r11 && r00 > r22) {
                const auto scale{2.0f * std::sqrt(1.0f + r00 - r11 - r22)};
                return transform::Quaternion{
                    (r21 - r12) / scale,
                    0.25f * scale,
                    (r01 + r10) / scale,
                    (r02 + r20) / scale
                };
            }

            if (r11 > r22) {
                const auto scale{2.0f * std::sqrt(1.0f + r11 - r00 - r22)};
                return transform::Quaternion{
                    (r02 - r20) / scale,
                    (r01 + r10) / scale,
                    0.25f * scale,
                    (r12 + r21) / scale
                };
            }

            const auto scale{2.0f * std::sqrt(1.0f + r22 - r00 - r11)};
            return transform::Quaternion{
                (r10 - r01) / scale,
                (r02 + r20) / scale,
                (r12 + r21) / scale,
                0.25f * scale
            };
        }()};

        this->transform.position = eye;
        this->transform.rotation = rotation;
    }

    [[nodiscard]] constexpr auto get_view_matrix() const
        -> math::Matrix<float, 4, 4> {
        constexpr auto UNIT_SCALE{transform::Scale{1.0f, 1.0f, 1.0f}};
        core::assert_eq(this->transform.scale, UNIT_SCALE);

        auto view{transform::Transform{
            {0.0f, 0.0f, 0.0f}, this->transform.rotation.conjugate(), UNIT_SCALE
        }
                      .get_matrix()};
        view.translate(
            {-this->transform.position.x,
             -this->transform.position.y,
             -this->transform.position.z}
        );
        return view;
    }

    constexpr auto update_projection(const float aspect_ratio) -> void {
        this->aspect_ratio = aspect_ratio;
        this->projection = math::Matrix<float, 4, 4>::perspective(
            this->fov_radians, this->aspect_ratio, this->z_near, this->z_far
        );
    }

  private:
    friend class scene::Scene;

    constexpr explicit Camera(
        const transform::Transform transform,
        const float fov_radians,
        const float aspect_ratio,
        const float z_near,
        const float z_far
    )
        : fov_radians{fov_radians}
        , aspect_ratio{aspect_ratio}
        , z_near{z_near}
        , z_far{z_far}
        , transform{transform}
        , projection{math::Matrix<float, 4, 4>::perspective(
              fov_radians, aspect_ratio, z_near, z_far
          )} {}
};

} // namespace goon::camera
