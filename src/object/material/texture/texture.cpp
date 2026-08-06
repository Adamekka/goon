#include "texture.hpp"
#include "core/defer.hpp"
#include "gl.hpp"
#include "stb/stb_image.h"

namespace goon::object::material::texture {

Texture::Texture(const std::filesystem::path& path) {
    glGenTextures(1, &this->id);
    this->bind();

    auto width{int32_t{}};
    auto height{int32_t{}};
    auto channels{int32_t{}};

    auto* const data{stbi_load(path.c_str(), &width, &height, &channels, 0)};

    defer({ stbi_image_free(data); });

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(Texture&& other) noexcept
    : id{std::exchange(other.id, 0)} {}

Texture::~Texture() {
    if (this->id != 0) {
        glDeleteTextures(1, &this->id);
    }
}

auto Texture::operator=(Texture&& other) noexcept -> Texture& {
    if (this != &other) {
        glDeleteTextures(1, &this->id);
        this->id = std::exchange(other.id, 0);
    }

    return *this;
}

auto Texture::bind() const -> void {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

auto Texture::unbind() -> void {
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace goon::object::material::texture
