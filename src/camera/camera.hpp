#pragma once

#include "matrix/matrix.hpp"

namespace goon::camera {

class Camera final {
  public:
    float fov_radians;
    float aspect_ratio;
    float z_near;
    float z_far;

    matrix::Matrix<float, 4, 4> transform;
    matrix::Matrix<float, 4, 4> projection;

    constexpr Camera(
        matrix::Matrix<float, 4, 4> transform,
        const float fov_radians,
        const float aspect_ratio,
        const float z_near,
        const float z_far
    )
        : fov_radians{fov_radians}
        , aspect_ratio{aspect_ratio}
        , z_near{z_near}
        , z_far{z_far} // NOLINTNEXTLINE(performance-move-const-arg)
        , transform{std::move(transform)}
        , projection{matrix::Matrix<float, 4, 4>::perspective(
              fov_radians, aspect_ratio, z_near, z_far
          )} {}

    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;

    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = delete;

    auto update_projection(float aspect_ratio) -> void;
};

} // namespace goon::camera
