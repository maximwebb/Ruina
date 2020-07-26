#version 330 core

layout(location=0) out vec4 color;

in vec4 v_color;
in vec2 v_tex_coord;
in float v_texture;

uniform bool u_is_texture;
uniform sampler2D u_textures[2];

void main() {
    if (u_is_texture) {
        int index = int(v_texture);
        color = texture(u_textures[index], v_tex_coord);
    }
    else {
        color = v_color;
    }
}
