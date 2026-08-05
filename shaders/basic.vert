#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;

uniform mat4 transform;

out vec4 vertex_color;
out vec2 texture_coordinates;

void main() {
    gl_Position = transform * vec4(pos, 1.0);
    vertex_color = color;
    texture_coordinates = uv;
}
