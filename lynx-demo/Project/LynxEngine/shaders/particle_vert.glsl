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



/*
// Example particle system

Resources::loadShader("particle", "shaders/particle_vert.glsl", "shaders/particle_frag.glsl");

// Create a mesh for the particle system.
std::vector<GLfloat> vertices;
std::vector<GLuint> elements;
int numParticles = 20000;
for (int i = 0; i < numParticles * 11; i += 11) {
	// vertex pos    normal     uv       color
	// 1, 1, 0,      0, 1, 0,   0, 1,    1, 1, 1

	// vertex positions are zero
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(0);

	// use random normals so that the particles travel in random directions
	glm::vec3 r = glm::sphericalRand<float>(1.0f);
	vertices.push_back(r.x);
	vertices.push_back(r.y);
	vertices.push_back(r.z);

	// use uv.u as the random speed factor for each particle
	vertices.push_back(glm::linearRand(10.0f, 100.0f));
	vertices.push_back(0); // just set uv.v to zero because it isn't used

	// give them random color values
	vertices.push_back(glm::linearRand<float>(0, 1.0f));
	vertices.push_back(glm::linearRand<float>(0, 1.0f));
	vertices.push_back(glm::linearRand<float>(0, 1.0f));
}

// Create an element index for each particle.
for (int j = 0; j < numParticles; j++) {
	elements.push_back(j);
}

// Create the mesh.
Resources::createMesh("particle", vertices, elements);

// Set the size of GL_POINTS for the particles.
glPointSize(0.5f);

// Create the game object.
GameObject *particles = new GameObject("particle_system");
particles->addComponent(new Graphics(particles, Resources::getMesh("particle"), Resources::getShader("particle"), nullptr, GL_POINTS));
particles->transform->setPosition(0, 0, 0);
scene->add(particles);

*/
