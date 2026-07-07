#pragma once

#include "gl.hpp"

namespace goon {

class Window {
  public:
    Window();

    Window(const Window&) = delete;
    Window(Window&&) = delete;

    ~Window();

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(Window&&) -> Window& = delete;

    auto run() -> void;

  private:
    GLFWwindow* window;
};

} // namespace goon
