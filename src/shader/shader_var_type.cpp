#include "shader_var_type.hpp"

namespace goon::shader {

ShaderVarType::ShaderVarType(Value value)
    : value{value} {}

ShaderVarType::ShaderVarType(uint32_t value)
    : value{static_cast<Value>(value)} {}

} // namespace goon::shader
