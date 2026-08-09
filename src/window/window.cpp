#include "window.hpp"
#include "core/panic.hpp"
#include "stb/stb_image.h"

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

auto Window::set_camera(camera::Camera& camera) -> void {
    this->camera = &camera;
}

auto Window::init() -> void {
    // MARK: OpenGL setup

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    this->window = glfwCreateWindow(
        goon::window::Window::WIDTH,
        goon::window::Window::HEIGHT,
        "goon",
        nullptr,
        nullptr
    );

    glfwMakeContextCurrent(this->window);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress));

    glfwSetWindowUserPointer(this->window, this);

    constexpr auto FRAMEBUFFER_SIZE_CALLBACK{
        []([[maybe_unused]] GLFWwindow* const window,
           const int32_t width,
           const int32_t height) -> void {
            glViewport(0, 0, width, height);

            if (width == 0 || height == 0) {
                // Minimized window
                return;
            }

            const auto* const self{
                static_cast<Window*>(glfwGetWindowUserPointer(window))
            };

            if (self->camera == nullptr) {
                goon::core::panic("Camera not set in Window");
            }

            self->camera->update_projection(
                static_cast<float>(width) / static_cast<float>(height)
            );
        }
    };

    FRAMEBUFFER_SIZE_CALLBACK(
        this->window, goon::window::Window::WIDTH, goon::window::Window::HEIGHT
    );

    glfwSetFramebufferSizeCallback(this->window, FRAMEBUFFER_SIZE_CALLBACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // MARK: stb setup

    stbi_set_flip_vertically_on_load(1);
}

auto Window::run(const std::function<void()>& callback) const -> void {
    if (this->window == nullptr) {
        goon::core::panic("Failed to initialize window");
    }

    while (glfwWindowShouldClose(this->window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        callback();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

} // namespace goon::window
