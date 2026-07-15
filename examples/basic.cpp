#include "mesh/mesh.hpp"
#include "shader/shader_manager.hpp"
#include "window/window.hpp"

auto main() -> int {
    goon::window::Window::instance().init();

    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.vert", goon::shader::ShaderType::Value::Vertex
    );
    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.frag", goon::shader::ShaderType::Value::Fragment
    );

    goon::shader::ShaderManager::instance().link();

    const auto triangle{goon::mesh::Mesh{std::array{
      goon::mesh::Point{-0.9f, -0.4f, 0.0f},
      goon::mesh::Point{-0.1f, -0.4f, 0.0f},
      goon::mesh::Point{-0.5f, 0.4f, 0.0f},
    }}};

    const auto rectangle{goon::mesh::Mesh{std::array{
      goon::mesh::Point{0.1f, -0.4f, 0.0f},
      goon::mesh::Point{0.9f, -0.4f, 0.0f},
      goon::mesh::Point{0.1f, 0.4f, 0.0f},
      goon::mesh::Point{0.9f, 0.4f, 0.0f},
    }}};

    goon::window::Window::instance().run([&triangle, &rectangle]() -> void {
        triangle.draw();
        rectangle.draw();
    });
}
