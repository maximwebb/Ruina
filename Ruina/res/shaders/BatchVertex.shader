#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coord;

uniform mat4 u_MVP;
uniform mat4 u_model;
uniform mat4 u_normal_model; // Inverse transpose of the model matrix

out vec4 wc_position;
out vec4 wc_normal;
out vec2 v_tex_coord;
flat out int v_texture_id;

void main() {
    gl_Position = u_MVP * position;
    wc_position = u_model * position;
    wc_normal = u_normal_model * position;
    v_tex_coord = tex_coord;
}