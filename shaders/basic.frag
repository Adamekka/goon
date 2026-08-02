#version 410 core

in vec4 vertex_color;
in vec2 texture_coordinates;

uniform sampler2D texture_sampler;

out vec4 color;

void main() {
    color = texture(texture_sampler, texture_coordinates) * vertex_color;
}
