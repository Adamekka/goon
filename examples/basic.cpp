#include "core/panic.hpp"
#include "input/input_manager.hpp"
#include "scene/scene.hpp"
#include "window/window.hpp"

auto main() -> int {
    // MARK: Create scene

    auto scene{goon::scene::Scene{}};

    // MARK: Create camera

    constexpr auto CAMERA_RADIUS{5.0f};

    auto& camera{scene.create_camera(
        goon::transform::Transform{
            {0.0f, 0.0f, CAMERA_RADIUS},
            goon::transform::Quaternion::identity(),
            {1.0f, 1.0f, 1.0f}
        },
        std::numbers::pi_v<float> / 4.0f,
        static_cast<float>(goon::window::Window::WIDTH)
            / static_cast<float>(goon::window::Window::HEIGHT)
    )};

    // MARK: Set camera

    goon::window::Window::instance().set_camera(camera);

    // MARK: Create window

    goon::window::Window::instance().init();

    // MARK: Create shader program

    auto shader_program{goon::scene::object::material::shader::ShaderProgram{}};

    // MARK: Compile shaders

    shader_program.compile(
        "examples/assets/shaders/basic.vert",
        goon::scene::object::material::shader::ShaderType{
            goon::scene::object::material::shader::ShaderType::Value::Vertex
        }
    );
    shader_program.compile(
        "examples/assets/shaders/basic.frag",
        goon::scene::object::material::shader::ShaderType{
            goon::scene::object::material::shader::ShaderType::Value::Fragment
        }
    );

    const auto& _{shader_program.link()};

    // MARK: Create textures

    const auto osaka_texture{[]() -> auto {
        auto result{goon::scene::object::material::texture::Texture::load(
            "examples/assets/textures/osaka.jpg"
        )};

        if (!result.has_value()) {
            goon::core::panic(result.error());
        }

        return std::move(*result);
    }()};

    const auto yui_texture{[]() -> auto {
        auto result{goon::scene::object::material::texture::Texture::load(
            "examples/assets/textures/yui.jpg"
        )};

        if (!result.has_value()) {
            goon::core::panic(result.error());
        }

        return std::move(*result);
    }()};

    // MARK: Create materials

    const auto osaka_material{
        goon::scene::object::material::Material{shader_program, osaka_texture}
    };

    const auto yui_material{
        goon::scene::object::material::Material{shader_program, yui_texture}
    };

    // MARK: Create objects from meshes

    auto* const osaka{scene.create_object(
        goon::scene::object::mesh::Mesh{
            std::array{
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{-0.4f, -0.4f, 0.0f},
                    goon::scene::object::mesh::Color{1.0f, 0.0f, 0.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{0.0f, 0.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                },
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{0.4f, -0.4f, 0.0f},
                    goon::scene::object::mesh::Color{0.0f, 1.0f, 0.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{1.0f, 0.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                },
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{0.0f, 0.4f, 0.0f},
                    goon::scene::object::mesh::Color{0.0f, 0.0f, 1.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{0.5f, 1.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                }
            },
            goon::scene::object::mesh::MeshDrawMode{
                goon::scene::object::mesh::MeshDrawMode::Value::Triangles
            }
        },
        osaka_material,
        goon::transform::Transform{
            {-0.5f, 0.0f, 0.0f},
            goon::transform::Quaternion::identity(),
            {1.0f, 2.0f, 1.0f}
        }
    )};

    auto* const yui{scene.create_object(
        goon::scene::object::mesh::Mesh{
            std::array{
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{-0.4f, -0.4f, 0.0f},
                    goon::scene::object::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{0.0f, 0.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                },
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{0.4f, -0.4f, 0.0f},
                    goon::scene::object::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{1.0f, 0.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                },
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{-0.4f, 0.4f, 0.0f},
                    goon::scene::object::mesh::Color{1.0f, 1.0f, 0.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{0.0f, 1.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                },
                goon::scene::object::mesh::Vertex{
                    goon::scene::object::mesh::Position{0.4f, 0.4f, 0.0f},
                    goon::scene::object::mesh::Color{1.0f, 0.0f, 1.0f, 1.0f},
                    goon::scene::object::mesh::TextureCoordinates{1.0f, 1.0f},
                    goon::scene::object::mesh::NormalVector{0.0f, 0.0f, 1.0f}
                }
            },
            goon::scene::object::mesh::MeshDrawMode{
                goon::scene::object::mesh::MeshDrawMode::Value::TriangleStrip
            }
        },
        yui_material,
        goon::transform::Transform{
            {0.5f, 0.0f, 0.0f},
            goon::transform::Quaternion::identity(),
            {1.0f, 1.0f, 1.0f}
        }
    )};

    // MARK: Create objects from glTF models

    auto* const miku{[&scene, &shader_program]() -> auto {
        auto result{scene.create_object(
            "examples/assets/models/miku.gltf",
            shader_program,
            goon::transform::Transform{
                {0.0f, 0.0f, 0.0f},
                goon::transform::Quaternion::identity(),
                {1.0f, 1.0f, 1.0f}
            }
        )};

        if (!result.has_value()) {
            goon::core::panic(result.error());
        }

        return *result;
    }()};

    // MARK: Create light

    const auto& _{scene.create_light(
        goon::scene::light::AmbientLight{{1.0f, 1.0f, 1.0f}, 0.5f},
        goon::scene::light::DiffuseLight{
            {1.0f, 1.0f, 1.0f}, 1.0f, {1.0f, 1.0f, 1.0f}
        }
    )};

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

        // MARK: Update camera

        const auto horizontal_radius{CAMERA_RADIUS * std::cos(camera_pitch)};
        const auto camera_position{std::array{
            horizontal_radius * std::sin(camera_yaw),
            CAMERA_RADIUS * std::sin(camera_pitch),
            horizontal_radius * std::cos(camera_yaw)
        }};
        camera.transform.position = camera_position;
        camera.look_at({0.0f, 0.0f, 0.0f});

        // MARK: Update objects

        const auto time{static_cast<float>(glfwGetTime())};

        osaka->transform.rotation
            = goon::transform::Quaternion::from_axis_angle(
                time, {0.0f, 1.0f, 0.0f}
            );

        yui->transform.rotation = goon::transform::Quaternion::from_axis_angle(
            time, {1.0f, 0.0f, 0.0f}
        );

        miku->transform.rotation = goon::transform::Quaternion::from_axis_angle(
            time, {0.0f, 1.0f, 0.0f}
        );

        // MARK: Draw

        scene.update();
    });
}
