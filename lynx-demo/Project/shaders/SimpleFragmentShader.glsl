#version 430 core

// Interpolated values from the vertex shaders.
in vec4 v2f_color;
 
// Ouput data.
out vec4 out_color;



void main() {
    // Output color = color specified in the vertex shader, interpolated between all 3 surrounding vertices.
    //out_color = v2f_color;

	// Inverted color.
	out_color = vec4(1.0 - v2f_color.r, 1.0 - v2f_color.g, 1.0 - v2f_color.b, 1.0);
}
