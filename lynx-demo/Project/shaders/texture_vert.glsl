#version 430 core

uniform mat4 uni_mvp;
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
out vec3 v2f_normal;
out vec2 v2f_uv;
out vec4 v2f_color;



void main() {
    gl_Position = uni_mvp * vec4(in_position, 1);

	// The normal.
	v2f_normal = in_normal;

	// UV of the vertex.
    v2f_uv = in_uv;

    // The color of each vertex will be interpolated to produce the color of each fragment.
    v2f_color = vec4(in_color, 1);
}
