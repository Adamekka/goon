#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

uniform vec3 offset;

out vec4 vertex_color;

void main() {
    gl_Position
        = vec4(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z, 1.0);
    vertex_color = color;
}
