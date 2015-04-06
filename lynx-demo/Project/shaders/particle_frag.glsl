#version 430 core

// Interpolated values from the vertex shaders.
in vec4 v2f_color;

// Ouput data.
out vec4 out_color;



void main() {
    // Output color = color of the texture at the specified UV.
    out_color = v2f_color;
}
