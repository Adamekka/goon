#include "shader_arg.hpp"

namespace goon::shader {

ShaderArg::ShaderArg(ShaderVarType type, int32_t location, int32_t array_size)
    : type{type}
    , location{location}
    , array_size{array_size} {}

} // namespace goon::shader
