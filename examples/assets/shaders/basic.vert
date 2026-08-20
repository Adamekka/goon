#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normal;

uniform mat4 model;
uniform mat3 normal_matrix;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertex_color;
out vec2 texture_coordinates;
out vec3 surface_normal;
out vec3 fragment_position;

void main() {
    vec4 world_position = model * vec4(pos, 1.0);
    gl_Position = projection * view * world_position;
    vertex_color = color;
    texture_coordinates = uv;
    surface_normal = normal_matrix * normal;
    fragment_position = world_position.xyz;
}
