#pragma once

#include "ambient_light.hpp"
#include "diffuse_light.hpp"
#include <optional>

namespace goon::scene {
class Scene;
} // namespace goon::scene

namespace goon::scene::light {

struct Light final {
    std::optional<AmbientLight> ambient_light;
    std::optional<DiffuseLight> diffuse_light;

  private:
    friend class scene::Scene;

    constexpr Light() = default;

    constexpr explicit Light(
        const std::optional<AmbientLight> ambient_light,
        const std::optional<DiffuseLight> diffuse_light
    )
        : ambient_light{ambient_light}
        , diffuse_light{diffuse_light} {}
};

} // namespace goon::scene::light
