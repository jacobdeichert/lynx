#version 430 core

uniform mat4 uni_mvp;
layout(location = 0) in vec3 in_position;

void main() {
    gl_Position = uni_mvp * vec4(in_position, 1);
}
