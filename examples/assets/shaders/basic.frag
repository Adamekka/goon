#version 410 core

in vec4 vertex_color;
in vec2 texture_coordinates;
in vec3 surface_normal;

uniform sampler2D texture_sampler;

uniform vec3 ambient_color;
uniform float ambient_intensity;

uniform vec3 diffuse_color;
uniform float diffuse_intensity;
uniform vec3 diffuse_direction;

out vec4 color;

void main() {
    // Color + Texture
    vec4 albedo = texture(texture_sampler, texture_coordinates) * vertex_color;

    // Ambient light
    vec3 ambient = ambient_color * ambient_intensity;

    // Diffuse light
    vec3 surface_normal_normalized = normalize(surface_normal);
    vec3 diffuse_direction_normalized = normalize(diffuse_direction);

    float diffuse_factor = max(
        dot(surface_normal_normalized, -diffuse_direction_normalized), 0.0
    );
    vec3 diffuse = diffuse_color * diffuse_intensity * diffuse_factor;

    color = vec4(albedo.rgb * (ambient + diffuse), albedo.a);
}
