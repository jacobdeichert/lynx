#version 430 core

uniform float uni_time;
uniform mat4 uni_model;
uniform mat3 uni_model_normals;
uniform mat4 uni_view;
uniform mat4 uni_projection;
layout(location = 0) in vec3 in_position;
/*
NOTE: When an attribute or uniform (ex: in_normal) is not used
in the shader, opengl removes it... and thus gives me an error
for when i use glGetAttribLocation().
Even if i pass it to the fragment shader (and still isn't used),
then it's still gunna be removed and give the opengl error.
*/
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_color;

// Output data will be sent to the fragment shader.
out vec4 v2f_color;



void main() {
    vec3 particlePosition = in_normal * (uni_time * in_uv.x);

    gl_Position = uni_projection * uni_view * uni_model * vec4(particlePosition, 1);

    // The color of each vertex will be interpolated to produce the color of each fragment.
    v2f_color = vec4(in_color, 1);
}
