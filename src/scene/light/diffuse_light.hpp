#pragma once

#include "core/assert.hpp"

namespace goon::scene::light {

struct DiffuseLight final {
    float r;
    float g;
    float b;
    float intensity;
    std::array<float, 3> direction;

    constexpr explicit DiffuseLight(
        const float r,
        const float g,
        const float b,
        const float intensity,
        const std::array<float, 3> direction
    )
        : r{r}
        , g{g}
        , b{b}
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
