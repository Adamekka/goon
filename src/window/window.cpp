#include "window.hpp"

namespace goon::window {

Window::~Window() {
    if (this->window != nullptr) {
        glfwDestroyWindow(this->window);
    }
    glfwTerminate();
}

auto Window::instance() -> Window& {
    static auto instance{Window{}};
    return instance;
}

auto Window::init() -> void {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    constexpr auto WIDTH{800};
    constexpr auto HEIGHT{600};

    this->window = glfwCreateWindow(WIDTH, HEIGHT, "goon", nullptr, nullptr);

    glfwMakeContextCurrent(this->window);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress));

    constexpr auto FRAMEBUFFER_SIZE_CALLBACK{
      []([[maybe_unused]] GLFWwindow* const window,
         const int32_t width,
         const int32_t height) -> void { glViewport(0, 0, width, height); }
    };

    FRAMEBUFFER_SIZE_CALLBACK(nullptr, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(this->window, FRAMEBUFFER_SIZE_CALLBACK);
}

auto Window::run(const std::function<void()>& callback) const -> void {
    if (this->window == nullptr) {
        throw std::runtime_error{"Window not initialized"};
    }

    while (!glfwWindowShouldClose(this->window)) {
        callback();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

} // namespace goon::window
