#version 430 core
uniform mat4 model, projection, view;
layout(location = 0) in vec3 position;


in  vec3 vNormal;
out vec4 color;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;


void main()
{
    gl_Position = projection * view * model * vec4(position, 1);
	
		
	// Transform vertex  position into eye coordinates
    vec3 pos = (view * model * vec4(position, 1)).xyz;
	vec3 L = normalize( (view * LightPosition).xyz - pos );
    vec3 E = normalize( -pos );
    vec3 H = normalize( L + E );
    
	// Transform vertex normal into eye coordinates
    vec3 N = normalize( view * model * vec4(vNormal, 0.0) ).xyz;
    
	// Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;
    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;
    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    
	if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 
    
	color = ambient + diffuse + specular;
    color.a = 1.0;
}
