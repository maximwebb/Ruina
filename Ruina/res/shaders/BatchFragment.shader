#version 460 core

layout(location=0) out vec4 color;

in vec4 wc_position;
in vec4 wc_normal;
in vec2 v_tex_coord;

uniform sampler2D u_textures[4];
uniform int u_texture_index;
uniform vec4 camera_position;
uniform int highlight;

void main() {
    vec4 light_position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    vec4 light_color = vec4(0.973f, 0.765f, 0.267f, 1.0f);
    vec4 light_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//     vec4 camera_position = vec4(5.0f, 5.0f, -5.0f, 1.0f);
    float k_a = 0.1f;
    float k_d = 2.0f;
    float k_s = .8f;
    float alpha = 8f;

    float intensity = 1.0f/(pow(length(light_position - wc_position), 2));

    vec4 L = normalize(light_position - wc_position);
    vec4 N = normalize(wc_normal);
    vec4 R = normalize(2 * dot(L, N) - L);
    vec4 V = normalize(camera_position - wc_position);

    int index = int(u_texture_index);
    vec4 surface_color = texture(u_textures[index], v_tex_coord);

    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    color += k_a * (surface_color);
    if (dot(L, N) > 0.0f) {
        color += dot(L, N) * k_d * surface_color;
    }
    if (dot(R, V) < 0.0f) {
        color += pow(-dot(R, V), alpha) * k_s * light_color;
    }

    color += vec4(0.3f * highlight);

}