#pragma once

#include <filesystem>

namespace goon::object::material::texture {

class Texture final {
  public:
    explicit Texture(const std::filesystem::path& path);

    Texture(const Texture&) = delete;
    Texture(Texture&&) noexcept;

    ~Texture();

    auto operator=(const Texture&) -> Texture& = delete;
    auto operator=(Texture&&) noexcept -> Texture&;

    auto bind() const -> void;
    static auto unbind() -> void;

  private:
    uint32_t id{0};
};

} // namespace goon::object::material::texture
