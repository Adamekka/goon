#include "texture.hpp"
#include "core/defer.hpp"
#include "gl.hpp"
#include "stb/stb_image.h"

namespace goon::mesh {

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

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}

auto Texture::bind() const -> void {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

auto Texture::unbind() -> void {
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace goon::mesh
