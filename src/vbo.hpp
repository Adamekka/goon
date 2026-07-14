#pragma once

#include "point.hpp"
#include <span>

namespace goon {

class VBO final {
  public:
    explicit VBO(std::span<const Point> vertices);

    VBO(const VBO&) = delete;
    VBO(VBO&&) = default;

    ~VBO();

    auto operator=(const VBO&) -> VBO& = delete;
    auto operator=(VBO&&) -> VBO& = default;

    auto bind() const -> void;
    static auto unbind() -> void;

  private:
    uint32_t id{0};
};

} // namespace goon
