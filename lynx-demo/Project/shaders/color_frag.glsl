#version 430 core

uniform sampler2D uni_texture;

// Interpolated values from the vertex shaders.
in vec3 v2f_normal;
in vec2 v2f_uv;
in vec4 v2f_color;

// Ouput data.
out vec4 out_color;



void main() {
    out_color = v2f_color;
}
