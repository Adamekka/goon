#pragma once

#include "gl.hpp"
#include "scene/camera/camera.hpp"
#include <functional>

namespace goon::window {

class Window final {
  public:
    static constexpr auto WIDTH{size_t{800}};
    static constexpr auto HEIGHT{size_t{600}};

    Window(const Window&) = delete;
    Window(Window&&) = delete;

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(Window&&) -> Window& = delete;

    [[nodiscard]] static auto instance() -> Window&;

    /// Set before calling init()
    auto set_camera(scene::camera::Camera& camera) -> void;

    auto init() -> void;

    auto run(const std::function<void()>& callback) const -> void;

  private:
    // nullptr means not ready
    GLFWwindow* window{nullptr};

    scene::camera::Camera* camera{nullptr};

    Window() = default;

    ~Window();
};

} // namespace goon::window
