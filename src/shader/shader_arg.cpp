#include "shader_arg.hpp"

namespace goon::shader {

ShaderArg::ShaderArg(
    const ShaderVarType type, const int32_t location, const int32_t array_size
)
    : type{type}
    , location{location}
    , array_size{array_size} {}

} // namespace goon::shader
