#include "window.hpp"

namespace goon {

Window::Window() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    constexpr int32_t WIDTH{800};
    constexpr int32_t HEIGHT{600};

    // NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
    this->window = glfwCreateWindow(WIDTH, HEIGHT, "goon", nullptr, nullptr);

    glfwMakeContextCurrent(this->window);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress));

    glViewport(0, 0, WIDTH, HEIGHT);

    constexpr auto FRAMEBUFFER_SIZE_CALLBACK{
      [](GLFWwindow*, int32_t width, int32_t height) -> void {
          glViewport(0, 0, width, height);
      }
    };

    glfwSetFramebufferSizeCallback(this->window, FRAMEBUFFER_SIZE_CALLBACK);
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

auto Window::run() -> void {
    while (!glfwWindowShouldClose(this->window)) {
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

} // namespace goon
