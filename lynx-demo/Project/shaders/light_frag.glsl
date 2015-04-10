#version 430 core

uniform sampler2D uni_texture;
uniform vec3 uni_camera_position;

// Interpolated values from the vertex shaders.
in vec3 v2f_normal;
in vec2 v2f_uv;
in vec4 v2f_color;
in vec3 v2f_fragment_position;

// Ouput data.
out vec4 out_color;


struct Light {
    vec3 position; // Useless for directional lights.
    vec3 direction;
    vec3 color;
    //vec4 diffuse;
    //vec4 specular;
};

Light directional_light = Light(
    vec3(0, 0, 0),
    vec3(0.5, 0.2, -0.7),
    vec3(0.4, 0.4, 0.4)
);

// struct Material {
//     vec4 ambient;
//     vec4 diffuse;
//     vec4 specular;
//     float shininess;
// };

// Material material1 = Material(
//     vec4(0.2, 0.2, 0.2, 1),
//     vec4(1.0, 0.8, 0.8, 1),
//     vec4(1, 1, 1, 1),
//     5
// );

void main() {
    // // else // point light or spotlight (or other kind of light)
    // // {
    // //     vec3 positionToLightSource = vec3(light0.position - position);
    // //     float distance = length(positionToLightSource);
    // //     lightDirection = normalize(positionToLightSource);
    // //     attenuation = 1.0 / (light0.constantAttenuation
    // //         + light0.linearAttenuation * distance
    // //         + light0.quadraticAttenuation * distance * distance);
    // //
    // //         if (light0.spotCutoff <= 90.0) // spotlight?
    // //         {
    // //             float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
    // //             if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
    // //             {
    // //                 attenuation = 0.0;
    // //             }
    // //             else
    // //             {
    // //                 attenuation = attenuation * pow(clampedCosine, light0.spotExponent);
    // //             }
    // //         }
    // //     }
    // diffuse_total = attenuation
    // * vec3(light1.diffuse) * vec3(material1.diffuse)
    // * max(0.0, dot(v2f_light_normals, light_direction));
    //
    // // light source on the wrong side?
    // if (dot(normal_direction, light_direction) < 0.0) {
    //     specular_total = vec3(0.0, 0.0, 0.0); // no specular reflection
    // } else /* light source on the right side */ {
    //     specular_total = attenuation * vec3(light1.specular) * vec3(material1.specular)
    //     * pow(max(0.0, dot(reflect(-light_direction, normal_direction), view_direction)), material1.shininess);
    // }

    // Ambient
    // The global illumination of objects when no light is hitting them.
    float ambient_strength = 0.4;
    vec3 ambient = ambient_strength * directional_light.color;


    // Diffuse
    vec3 norm = normalize(v2f_normal);
    vec3 lightDir = normalize(directional_light.direction); // directional light?
    //vec3 lightDir = normalize(light1.position - v2f_fragment_position); // point light?
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * directional_light.color;

    // Specular
    float specular_strength = 1.5;
    vec3 viewDir = normalize(uni_camera_position - v2f_fragment_position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specular_strength * spec * directional_light.color;

    vec3 result = ambient + diffuse + specular;// * v2f_color;
    out_color = texture(uni_texture, v2f_uv) * vec4(result, 1);

    //out_color = vec4(v2f_normal, 1);
    //out_color.a = 0.4;
    //if (texture(uni_texture, v2f_uv).a == 0) discard;
	// Turn transparent parts of a texture pink.
	//if (texture(uni_texture, v2f_uv).a < 1) out_color = vec4(1,0,1,1);
}
