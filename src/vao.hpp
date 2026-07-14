#pragma once

#include "vbo.hpp"

namespace goon {

class VAO final {
  public:
    explicit VAO(const VBO& vbo);

    VAO(const VAO&) = delete;
    VAO(VAO&&) = default;

    ~VAO();

    auto operator=(const VAO&) -> VAO& = delete;
    auto operator=(VAO&&) -> VAO& = default;

    auto bind() const -> void;
    static auto unbind() -> void;

  private:
    uint32_t id{0};
};

} // namespace goon
