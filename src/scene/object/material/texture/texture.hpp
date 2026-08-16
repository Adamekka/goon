#pragma once

#include <expected>
#include <filesystem>
#include <span>

namespace goon::scene::object::material::texture {

class Texture final {
  public:
    Texture(const Texture&) = delete;
    Texture(Texture&&) noexcept;

    ~Texture();

    auto operator=(const Texture&) -> Texture& = delete;
    auto operator=(Texture&&) noexcept -> Texture&;

    [[nodiscard]] static auto load(const std::filesystem::path& path)
        -> std::expected<Texture, std::string>;

    [[nodiscard]] static auto load(std::span<const uint8_t> data)
        -> std::expected<Texture, std::string>;

    auto bind() const -> void;
    static auto unbind() -> void;

  private:
    uint32_t id{0};

    Texture(const uint8_t* pixels, int32_t width, int32_t height);
};

} // namespace goon::scene::object::material::texture
