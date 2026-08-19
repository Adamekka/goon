#pragma once

#include "core/assert.hpp"

namespace goon::scene::light {

struct DiffuseLight final {
    std::array<float, 3> color;
    float intensity;
    std::array<float, 3> direction;

    constexpr explicit DiffuseLight(
        const std::array<float, 3> color,
        const float intensity,
        const std::array<float, 3> direction
    )
        : color{color}
        , intensity{intensity}
        , direction{direction} {
        const auto direction_length_squared{
            (direction[0] * direction[0]) + (direction[1] * direction[1])
            + (direction[2] * direction[2])
        };
        core::assert_that(std::isfinite(direction_length_squared));
        core::assert_that(direction_length_squared > 0.0f);
    }
};

} // namespace goon::scene::light
