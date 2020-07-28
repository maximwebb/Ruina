#version 330 core

layout(location=0) out vec4 color;

in vec4 v_color;
in vec2 v_tex_coord;
flat in int v_texture_id;

uniform sampler2D u_textures[2];

void main() {
    switch(v_texture_id) {
        case 0: color = v_color; break;
        case 1: color = texture(u_textures[0], v_tex_coord); break;
        case 2: color = texture(u_textures[1], v_tex_coord); break;
    }
}
