#version 430 core

uniform sampler2D uni_texture;

// Interpolated values from the vertex shaders.
in vec3 v2f_normal;
in vec2 v2f_uv;
in vec4 v2f_color;
in vec3 v2f_light_normals;
in mat4 v2f_inverse_view;
in vec4 v2f_position;

// Ouput data.
out vec4 out_color;


struct Light {
    vec4 position;
    vec3 direction;
    vec4 diffuse;
    vec4 specular;
};

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

Light light1 = Light(
    vec4(4, 4, 4, 1),
    vec3(0, -1, 1),
    vec4(1, 1, 1, 1),
    vec4(1, 1, 1, 1)
);

Material material1 = Material(
    vec4(0.2, 0.2, 0.2, 1.0),
    vec4(1.0, 0.8, 0.8, 1.0),
    vec4(1.0, 1.0, 1.0, 1.0),
    5.0
);

void main() {
    vec3 ambient_total = vec3(0, 1, 0);
    vec3 diffuse_total = vec3(0, 0, 1);
    vec3 specular_total = vec3(0, 0, 1);


    vec3 normal_direction = normalize(v2f_light_normals);
    vec3 view_direction = normalize(vec3(v2f_inverse_view * vec4(0.0, 0.0, 0.0, 1.0) - v2f_position));


    vec4 scene_ambient = vec4(0.4, 0.4, 0.4, 1.0);
    ambient_total = vec3(scene_ambient) * vec3(material1.ambient);

    // directional light
    //if (light0.position.w == 0.0) {
        float attenuation = 1.0; // no attenuation
        vec3 light_direction = normalize(vec3(light1.position));
    //}
    // else // point light or spotlight (or other kind of light)
    // {
    //     vec3 positionToLightSource = vec3(light0.position - position);
    //     float distance = length(positionToLightSource);
    //     lightDirection = normalize(positionToLightSource);
    //     attenuation = 1.0 / (light0.constantAttenuation
    //         + light0.linearAttenuation * distance
    //         + light0.quadraticAttenuation * distance * distance);
    //
    //         if (light0.spotCutoff <= 90.0) // spotlight?
    //         {
    //             float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
    //             if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
    //             {
    //                 attenuation = 0.0;
    //             }
    //             else
    //             {
    //                 attenuation = attenuation * pow(clampedCosine, light0.spotExponent);
    //             }
    //         }
    //     }
    diffuse_total = attenuation
    * vec3(light1.diffuse) * vec3(material1.diffuse)
    * max(0.0, dot(v2f_light_normals, light_direction));

    // light source on the wrong side?
    if (dot(normal_direction, light_direction) < 0.0) {
        specular_total = vec3(0.0, 0.0, 0.0); // no specular reflection
    } else /* light source on the right side */ {
        specular_total = attenuation * vec3(light1.specular) * vec3(material1.specular)
        * pow(max(0.0, dot(reflect(-light_direction, normal_direction), view_direction)), material1.shininess);
    }

    // Output color = color of the texture at the specified UV.
    //out_color = vec4(ambient_total + diffuse_total + specular_total, 1.0);
    out_color = texture(uni_texture, v2f_uv) * vec4(ambient_total + diffuse_total + specular_total, 1.0);// * v2f_color + vec4(v2f_normal, 1);
    //out_color = vec4(v2f_normal, 1);
    //out_color.a = 0.4;
    //if (texture(uni_texture, v2f_uv).a == 0) discard;
	// Turn transparent parts of a texture pink.
	//if (texture(uni_texture, v2f_uv).a < 1) out_color = vec4(1,0,1,1);
}
