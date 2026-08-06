#include "object/object.hpp"
#include "window/window.hpp"
#include <numbers>

auto main() -> int {
    // MARK: Init

    goon::window::Window::instance().init();

    // MARK: Create shader programs

    auto shader_program{goon::object::material::shader::ShaderProgram{}};

    // MARK: Compile shaders

    shader_program.compile(
        "examples/assets/shaders/basic.vert",
        goon::object::material::shader::ShaderType{
          goon::object::material::shader::ShaderType::Value::Vertex
        }
    );
    shader_program.compile(
        "examples/assets/shaders/basic.frag",
        goon::object::material::shader::ShaderType{
          goon::object::material::shader::ShaderType::Value::Fragment
        }
    );

    auto& _{shader_program.link()};

    // MARK: Create textures

    const auto osaka_texture{goon::object::material::texture::Texture{
      "examples/assets/textures/osaka.jpg"
    }};

    const auto yui_texture{goon::object::material::texture::Texture{
      "examples/assets/textures/yui.jpg"
    }};

    // MARK: Create materials

    const auto osaka_material{
      goon::object::material::Material{shader_program, osaka_texture}
    };

    const auto yui_material{
      goon::object::material::Material{shader_program, yui_texture}
    };

    // MARK: Create objects

    auto osaka{goon::object::Object{
      goon::object::mesh::Mesh{std::array{
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{-0.4f, -0.4f, 0.0f},
          goon::object::mesh::Color{1.0f, 0.0f, 0.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{0.0f, 0.0f}
        },
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{0.4f, -0.4f, 0.0f},
          goon::object::mesh::Color{0.0f, 1.0f, 0.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{1.0f, 0.0f}
        },
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{0.0f, 0.4f, 0.0f},
          goon::object::mesh::Color{0.0f, 0.0f, 1.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{0.5f, 1.0f}
        }
      }},
      osaka_material,
      goon::matrix::Matrix<float, 4, 4>::identity()
    }};

    auto yui{goon::object::Object{
      goon::object::mesh::Mesh{std::array{
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{-0.4f, -0.4f, 0.0f},
          goon::object::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{0.0f, 0.0f}
        },
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{0.4f, -0.4f, 0.0f},
          goon::object::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{1.0f, 0.0f}
        },
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{-0.4f, 0.4f, 0.0f},
          goon::object::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{0.0f, 1.0f}
        },
        goon::object::mesh::Vertex{
          goon::object::mesh::Pos{0.4f, 0.4f, 0.0f},
          goon::object::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
          goon::object::mesh::TextureCoordinates{1.0f, 1.0f}
        }
      }},
      yui_material,
      goon::matrix::Matrix<float, 4, 4>::identity()
    }};

    // MARK: Run

    goon::window::Window::instance().run([&osaka, &yui]() -> void {
        // MARK: Transformation matrix

        auto osaka_transform{goon::matrix::Matrix<float, 4, 4>::identity()};
        osaka_transform.translate(std::array{-0.5f, 0.0f, 0.0f});

        const auto time{static_cast<float>(glfwGetTime())};
        constexpr auto ROTATION_SPEED{std::numbers::pi_v<float> / 2.0f};
        osaka_transform.rotate_z(time * ROTATION_SPEED);

        osaka_transform.scale(std::array{1.0f, 2.0f, 1.0f});

        osaka.transform = osaka_transform;

        auto yui_transform{goon::matrix::Matrix<float, 4, 4>::identity()};
        yui_transform.translate(std::array{0.5f, 0.0f, 0.0f});
        yui_transform.rotate_z(-time * ROTATION_SPEED);
        yui_transform.scale(std::array{1.0f, 1.0f, 1.0f});
        yui.transform = yui_transform;

        // MARK: Draw

        osaka.draw();
        yui.draw();
    });
}
