#version 430 core

uniform sampler2D uni_texture;

// Interpolated values from the vertex shaders.
in vec3 v2f_normal;
in vec2 v2f_uv;
in vec4 v2f_color;

// Ouput data.
out vec4 out_color;



void main() {
    // Output color = color of the texture at the specified UV.
    out_color = texture(uni_texture, v2f_uv) * v2f_color * vec4(v2f_normal, 1);
    //out_color = vec4(v2f_normal, 1);
    //out_color.a = texture(uni_texture, v2f_uv).a;
    //if (texture(uni_texture, v2f_uv).a == 0) discard;
	// Turn transparent parts of a texture pink.
	//if (texture(uni_texture, v2f_uv).a < 1) out_color = vec4(1,0,1,1);
}
