#include "input/input_manager.hpp"
#include "object/object.hpp"
#include "window/window.hpp"

auto main() -> int {
    // MARK: Create camera

    constexpr auto CAMERA_RADIUS{3.0f};

    auto camera{goon::camera::Camera{
        goon::matrix::Matrix<float, 4, 4>::look_at(
            {0.0f, 0.0f, CAMERA_RADIUS}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}
        ),
        std::numbers::pi_v<float> / 4.0f,
        static_cast<float>(goon::window::Window::WIDTH)
            / static_cast<float>(goon::window::Window::HEIGHT),
        0.1f,
        100.0f
    }};

    // MARK: Set camera

    goon::window::Window::instance().set_camera(camera);

    // MARK: Create window

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

    auto camera_yaw{0.0f};
    auto camera_pitch{0.0f};

    goon::window::Window::instance().run([&]() -> void {
        // MARK: Input

        constexpr auto ORBIT_SPEED{0.02f};
        camera_yaw += goon::input::InputManager::is_key_down(GLFW_KEY_D)
                        ? ORBIT_SPEED
                        : 0.0f;
        camera_yaw -= goon::input::InputManager::is_key_down(GLFW_KEY_A)
                        ? ORBIT_SPEED
                        : 0.0f;
        camera_pitch += goon::input::InputManager::is_key_down(GLFW_KEY_W)
                          ? ORBIT_SPEED
                          : 0.0f;
        camera_pitch -= goon::input::InputManager::is_key_down(GLFW_KEY_S)
                          ? ORBIT_SPEED
                          : 0.0f;
        camera_pitch = std::clamp(camera_pitch, -1.5f, 1.5f);

        const auto horizontal_radius{CAMERA_RADIUS * std::cos(camera_pitch)};
        const auto camera_position{std::array{
            horizontal_radius * std::sin(camera_yaw),
            CAMERA_RADIUS * std::sin(camera_pitch),
            horizontal_radius * std::cos(camera_yaw)
        }};
        camera.transform = goon::matrix::Matrix<float, 4, 4>::look_at(
            camera_position, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}
        );

        // MARK: Transformation matrix

        auto osaka_transform{goon::matrix::Matrix<float, 4, 4>::identity()};
        osaka_transform.translate(std::array{-0.5f, 0.0f, 0.0f});
        osaka_transform.scale(std::array{1.0f, 2.0f, 1.0f});
        osaka.transform = osaka_transform;

        auto yui_transform{goon::matrix::Matrix<float, 4, 4>::identity()};
        yui_transform.translate(std::array{0.5f, 0.0f, 0.0f});
        yui_transform.scale(std::array{1.0f, 1.0f, 1.0f});
        yui.transform = yui_transform;

        // MARK: Draw

        osaka.draw(camera);
        yui.draw(camera);
    });
}
