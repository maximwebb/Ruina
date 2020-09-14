#version 330 core

layout(location=0) out vec4 color;

in vec4 wc_position;
in vec4 wc_normal;
in vec2 v_tex_coord;

uniform sampler2D u_textures[2];

void main() {
    vec4 light_position = vec4(5.0f, 5.0f, 0.0f, 1.0f);
    vec4 light_color = vec4(0.973f, 0.765f, 0.267f, 1.0f);
    vec4 camera_position = vec4(0.0f, 0.0f, -10.0f, 1.0f);
    float k_a = 0.3f;
    float k_d = 5.0f;
    float k_s = 1.0f;
    int alpha = 5;

    float intensity = 1.0f/(pow(length(light_position - wc_position), 2));

    vec4 L = normalize(light_position - wc_position);
    vec4 N = normalize(wc_normal);
    vec4 R = normalize(2 * dot(L, N) - L);
    vec4 V = normalize(camera_position - wc_position);

    vec4 surface_color = texture(u_textures[0], v_tex_coord);
//    switch(v_texture_id) {
//        case 0: surface_color = v_color; break;
//        case 1: surface_color = texture(u_textures[0], v_tex_coord); break;
//        case 2: surface_color = texture(u_textures[1], v_tex_coord); break;
//    }

    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    color += k_a * (surface_color);
    if (dot(L, N) > 0.0f) {
        color += dot(L, N) * k_d * surface_color;
    }
    if (dot(R, V) < 0.0f) {
        color += pow(-dot(R, V), alpha) * k_s * light_color;
    }
}