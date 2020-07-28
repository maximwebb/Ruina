#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in float texture_id;

uniform mat4 u_MVP;

out vec4 v_color;
out vec2 v_tex_coord;
flat out int v_texture_id;

void main() {
    gl_Position = u_MVP * position;
    v_color = a_color;
    v_tex_coord = tex_coord;
    v_texture_id = int(texture_id);
}