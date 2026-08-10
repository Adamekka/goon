#pragma once

#include <array>

namespace goon::scene::light {

struct AmbientLight final {
    std::array<float, 3> color;
    float intensity;

    constexpr explicit AmbientLight(std::array<float, 3> color, float intensity)
        : color{color}
        , intensity{intensity} {}
};

} // namespace goon::scene::light
