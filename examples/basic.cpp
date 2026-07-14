#include "mesh.hpp"
#include "shader_manager.hpp"
#include "window.hpp"

auto main() -> int {
    goon::Window::instance().init();

    goon::ShaderManager::instance().compile(
        "shaders/basic.vert", goon::ShaderType::Value::Vertex
    );
    goon::ShaderManager::instance().compile(
        "shaders/basic.frag", goon::ShaderType::Value::Fragment
    );

    goon::ShaderManager::instance().link();

    const auto triangle{std::array{
      goon::Point{-0.9f, -0.4f, 0.0f},
      goon::Point{-0.1f, -0.4f, 0.0f},
      goon::Point{-0.5f, 0.4f, 0.0f}
    }};

    const auto rectangle{std::array{
      goon::Point{0.1f, -0.4f, 0.0f},
      goon::Point{0.9f, -0.4f, 0.0f},
      goon::Point{0.1f, 0.4f, 0.0f},
      goon::Point{0.9f, 0.4f, 0.0f}
    }};

    goon::Window::instance().run([&triangle, &rectangle]() -> void {
        goon::Mesh{triangle}.draw();
        goon::Mesh{rectangle}.draw();
    });
}
