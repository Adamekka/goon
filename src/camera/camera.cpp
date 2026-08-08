#include "camera.hpp"

namespace goon::camera {

auto Camera::update_projection(const float aspect_ratio) -> void {
    this->aspect_ratio = aspect_ratio;
    this->projection = matrix::Matrix<float, 4, 4>::perspective(
        this->fov_radians, this->aspect_ratio, this->z_near, this->z_far
    );
}

} // namespace goon::camera
