#version 410 core

in vec4 vertex_color;
in vec2 texture_coordinates;

uniform sampler2D texture_sampler;

uniform vec3 ambient_light_color;
uniform float ambient_strength;

out vec4 color;

void main() {
    color = texture(texture_sampler, texture_coordinates) * vertex_color
          * vec4(ambient_light_color * ambient_strength, 0.0);
}
