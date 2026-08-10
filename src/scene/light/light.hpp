#pragma once

#include "ambient_light.hpp"
#include <optional>

namespace goon::scene::light {

struct Light final {
    std::optional<AmbientLight> ambient_light;

    constexpr explicit Light(
        const std::optional<AmbientLight> ambient_light = std::nullopt
    )
        : ambient_light{ambient_light} {}
};

} // namespace goon::scene::light
