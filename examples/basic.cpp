#include "mesh/mesh.hpp"
#include "shader/shader_manager.hpp"
#include "window/window.hpp"

auto main() -> int {
    // MARK: Init

    goon::window::Window::instance().init();

    // MARK: Create shaders

    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.vert", goon::shader::ShaderType::Value::Vertex
    );
    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.frag", goon::shader::ShaderType::Value::Fragment
    );

    // MARK: Pass shader data

    auto& shader_args{goon::shader::ShaderManager::instance().link()};

    shader_args.at("vertex_color")
        .pass_data(
            std::array{
              1.0f,
              1.0f,
              1.0f,
              1.0f,
            }
        );

    assert(goon::shader::ShaderManager::instance().validate());

    // MARK: Create meshes

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

    // MARK: Run

    goon::window::Window::instance().run([&triangle, &rectangle]() -> void {
        triangle.draw();
        rectangle.draw();
    });
}
