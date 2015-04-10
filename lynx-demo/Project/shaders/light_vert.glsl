#version 430 core

uniform mat4 uni_model;
//uniform mat3 uni_normal;
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
out vec3 v2f_normal;
out vec2 v2f_uv;
out vec4 v2f_color;
out vec3 v2f_fragment_position;


void main() {
    v2f_fragment_position = vec3(uni_model * vec4(in_position, 1));

    // proj * view * model * in_position
    gl_Position = uni_projection * uni_view * uni_model * vec4(in_position, 1);


	// The normal in world space.
    // Should do this on the CPU though. For now, faster on GPU for small worlds.
    // test this instead: mat3(inverse(transpose(uni_model))) * in_normal
	v2f_normal = mat3(transpose(inverse(uni_model))) * in_normal;

	// UV of the vertex.
    v2f_uv = in_uv;

    // The color of each vertex will be interpolated to produce the color of each fragment.
    v2f_color = vec4(in_color, 1);
}
