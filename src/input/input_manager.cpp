#include "input_manager.hpp"
#include "gl.hpp"
#include <cassert>

namespace goon::input {

auto InputManager::is_key_down(const int32_t key) -> bool {
    assert(key >= 0 && key <= GLFW_KEY_LAST);
    auto* const window{glfwGetCurrentContext()};
    assert(window != nullptr);
    return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace goon::input
