#pragma once

#include <filesystem>

namespace goon::mesh {

class Texture final {
  public:
    explicit Texture(const std::filesystem::path& path);

    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;

    ~Texture();

    auto operator=(const Texture&) -> Texture& = delete;
    auto operator=(Texture&&) -> Texture& = default;

    auto bind() const -> void;
    static auto unbind() -> void;

  private:
    uint32_t id{0};
};

} // namespace goon::mesh
