#version 430 core

uniform sampler2D uni_texture;

// Interpolated values from the vertex shaders.
in vec3 v2f_normal;
in vec2 v2f_uv;
in vec4 v2f_color;
in vec3 v2f_light_normals;
in mat4 v2f_inverse_view;
in vec4 v2f_position;
in vec4 v2f_eye_position;

// Ouput data.
out vec4 out_color;


struct Light {
    vec4 position;
    vec3 direction;
    vec4 diffuse;
    vec4 specular;
};

Light light1 = Light(
    vec4(-400, 400, -400, 1),
    vec3(-1, 1, -1),
    vec4(1, 1, 1, 1),
    vec4(1, 1, 1, 1)
);

void main() {
    
	vec3 light_dir = normalize(light1.direction);
	float intensity = dot(light_dir, v2f_light_normals);
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 outc;

	float silhouette = max(dot(v2f_light_normals, normalize(-v2f_eye_position.xyz)), 0.0);

	
	if (silhouette < 0.2){
		outc = color;	
	}else if (intensity > 0.95){
		outc = vec4(1.0, 0.5, 0.5, 1.0);
	}else if (intensity > 0.5){
		outc = vec4(0.6, 0.3, 0.3, 1.0);
	}else if (intensity > 0.25){
		outc = vec4(0.4, 0.2, 0.2, 1.0);
	}else{
		outc = vec4(0.2, 0.1, 0.1, 1.0);
	}

    out_color = outc;
    
}
