#version 430 core

uniform mat4 uni_mvp;
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

// Output data will be sent to the fragment shader.
out vec4 v2f_color;



void main() {
    gl_Position = uni_mvp * vec4(in_position, 1);

    // The color of each vertex will be interpolated to produce the color of each fragment.
    v2f_color = vec4(in_color, 1);
}
