#include "mesh/mesh.hpp"
#include "shader/shader_manager.hpp"
#include "window/window.hpp"
#include <cmath>

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

    shader_args.at("offset").pass_data(std::array{0.0f, 0.0f, 0.0f});

    assert(goon::shader::ShaderManager::instance().validate());

    // MARK: Create meshes

    const auto triangle{goon::mesh::Mesh{std::array{
      goon::mesh::Vertex{
        goon::mesh::Pos{-0.9f, -0.4f, 0.0f},
        goon::mesh::Color{1.0f, 0.0f, 0.0f, 1.0f}
      },
      goon::mesh::Vertex{
        goon::mesh::Pos{-0.1f, -0.4f, 0.0f},
        goon::mesh::Color{0.0f, 1.0f, 0.0f, 1.0f}
      },
      goon::mesh::Vertex{
        goon::mesh::Pos{-0.5f, 0.4f, 0.0f},
        goon::mesh::Color{0.0f, 0.0f, 1.0f, 1.0f}
      }
    }}};

    const auto rectangle{goon::mesh::Mesh{std::array{
      goon::mesh::Vertex{
        goon::mesh::Pos{0.1f, -0.4f, 0.0f},
        goon::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f}
      },
      goon::mesh::Vertex{
        goon::mesh::Pos{0.9f, -0.4f, 0.0f},
        goon::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f}
      },
      goon::mesh::Vertex{
        goon::mesh::Pos{0.1f, 0.4f, 0.0f},
        goon::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f}
      },
      goon::mesh::Vertex{
        goon::mesh::Pos{0.9f, 0.4f, 0.0f},
        goon::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f}
      }
    }}};

    // MARK: Run

    goon::window::Window::instance().run(
        [&shader_args, &triangle, &rectangle]() -> void {
            // MARK: Pass shader data at runtime

            const auto time{static_cast<float>(glfwGetTime())};
            const auto offset_y{std::sin(time) / 2.0f};

            shader_args.at("offset").pass_data(
                std::array{0.0f, offset_y, 0.0f}
            );

            assert(goon::shader::ShaderManager::instance().validate());

            // MARK: Draw

            triangle.draw();
            rectangle.draw();
        }
    );
}
