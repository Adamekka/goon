#version 410 core

in vec4 vertex_color;
in vec2 texture_coordinates;
in vec3 surface_normal;
in vec3 fragment_position;

uniform sampler2D texture_sampler;

uniform vec3 ambient_color;
uniform float ambient_intensity;

uniform vec3 diffuse_color;
uniform float diffuse_intensity;
uniform vec3 diffuse_direction;

uniform vec3 specular_color;
uniform float specular_intensity;
uniform vec3 specular_direction;

uniform vec3 camera_position;
uniform float shininess;

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

    // Specular light
    vec3 specular_direction_normalized = normalize(specular_direction);
    vec3 view_direction = normalize(camera_position - fragment_position);
    vec3 reflection_direction = reflect(
        specular_direction_normalized, surface_normal_normalized
    );

    float specular_factor = 0.0;
    if (
        shininess > 0.0
        && dot(surface_normal_normalized, -specular_direction_normalized) > 0.0
    ) {
        specular_factor = pow(
            max(dot(view_direction, reflection_direction), 0.0), shininess
        );
    }
    vec3 specular = specular_color * specular_intensity * specular_factor;

    color = vec4(albedo.rgb * (ambient + diffuse) + specular, albedo.a);
}
