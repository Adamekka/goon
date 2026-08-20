#pragma once

namespace goon::scene::light {

struct AmbientLight final {
    float r;
    float g;
    float b;
    float intensity;

    constexpr AmbientLight(
        const float r, const float g, const float b, const float intensity
    )
        : r{r}
        , g{g}
        , b{b}
        , intensity{intensity} {}
};

} // namespace goon::scene::light
