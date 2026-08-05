#include "mesh/mesh.hpp"
#include "shader/shader_manager.hpp"
#include "window/window.hpp"
#include <numbers>

auto main() -> int {
    // MARK: Init

    goon::window::Window::instance().init();

    // MARK: Compile shaders

    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.vert", goon::shader::ShaderType::Value::Vertex
    );
    goon::shader::ShaderManager::instance().compile(
        "shaders/basic.frag", goon::shader::ShaderType::Value::Fragment
    );

    auto& shader_args{goon::shader::ShaderManager::instance().link()};

    // MARK: Create textures

    const auto texture{
      std::make_shared<const goon::mesh::Texture>("examples/osaka.jpg")
    };

    // MARK: Create meshes

    const auto triangle{goon::mesh::Mesh{
      std::array{
        goon::mesh::Vertex{
          goon::mesh::Pos{-0.9f, -0.4f, 0.0f},
          goon::mesh::Color{1.0f, 0.0f, 0.0f, 1.0f},
          goon::mesh::TextureCoordinates{0.0f, 0.0f}
        },
        goon::mesh::Vertex{
          goon::mesh::Pos{-0.1f, -0.4f, 0.0f},
          goon::mesh::Color{0.0f, 1.0f, 0.0f, 1.0f},
          goon::mesh::TextureCoordinates{1.0f, 0.0f}
        },
        goon::mesh::Vertex{
          goon::mesh::Pos{-0.5f, 0.4f, 0.0f},
          goon::mesh::Color{0.0f, 0.0f, 1.0f, 1.0f},
          goon::mesh::TextureCoordinates{0.5f, 1.0f}
        }
      },
      texture
    }};

    const auto rectangle{goon::mesh::Mesh{
      std::array{
        goon::mesh::Vertex{
          goon::mesh::Pos{0.1f, -0.4f, 0.0f},
          goon::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
          goon::mesh::TextureCoordinates{0.0f, 1.0f}
        },
        goon::mesh::Vertex{
          goon::mesh::Pos{0.9f, -0.4f, 0.0f},
          goon::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
          goon::mesh::TextureCoordinates{1.0f, 1.0f}
        },
        goon::mesh::Vertex{
          goon::mesh::Pos{0.1f, 0.4f, 0.0f},
          goon::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
          goon::mesh::TextureCoordinates{0.0f, 0.0f}
        },
        goon::mesh::Vertex{
          goon::mesh::Pos{0.9f, 0.4f, 0.0f},
          goon::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
          goon::mesh::TextureCoordinates{1.0f, 0.0f}
        }
      },
      texture
    }};

    // MARK: Run

    goon::window::Window::instance().run(
        [&shader_args, &triangle, &rectangle]() -> void {
            // MARK: Transformation matrix

            auto transform{goon::shader::Matrix<float, 4, 4>::identity()};
            transform.scale(std::array{0.5f, 0.5f, 0.5f});

            const auto time{static_cast<float>(glfwGetTime())};
            constexpr auto ROTATION_SPEED{std::numbers::pi_v<float> / 2.0f};
            transform.rotate_z(time * ROTATION_SPEED);

            // MARK: Pass shader data

            shader_args.at("transform").pass_data(transform);

            // MARK: Draw

            triangle.draw();
            rectangle.draw();
        }
    );
}
