#pragma once

#include "gl.hpp"
#include <functional>

namespace goon::window {

class Window final {
  public:
    Window(const Window&) = delete;
    Window(Window&&) = delete;

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(Window&&) -> Window& = delete;

    static auto instance() -> Window&;

    auto init() -> void;

    auto run(const std::function<void()>& callback) const -> void;

  private:
    // nullptr means not ready
    GLFWwindow* window{nullptr};

    Window() = default;

    ~Window();
};

} // namespace goon::window
