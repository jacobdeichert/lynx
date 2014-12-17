#pragma once
#include <GL/glew.h>
#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "Mesh.h"


namespace lynx {
	class Shader {
	public:
		std::string name;
		std::string vertexFile;
		std::string fragmentFile;


		Shader(std::string _name, std::string _vertexFile, std::string _fragmentFile, GLuint _programID);
		~Shader();
		void activate(Mesh *_mesh, bool isCurrentShader);

		/**
		 * TODO: make this update all uniforms that will be
		 * stored in an array in the future.
		 *
		 * For now, it just takes in the MVP.
		 */
		void updateUniforms(glm::mat4 _mvp);

		/**
		 * Location of attributes in the shader.
		 * 0: in_position
		 * 1: in_normal
		 * 2: in_uv
		 * 3: in_color
		 *
		 * TODO: make an array of attributes that the user will set
		 * when they create a shader.
		 */
		GLint attributePosition;
		GLint attributeNormal;
		GLint attributeUV;
		GLint attributeColor;
	private:
		GLuint programID;

		/**
		 * Location of uniforms in shader.
		 * uniformMVP: The uni_mvp (model, view, projection) matrix in the shader.
		 * uniformTexture: The uni_texture in the shader.
		 *
		 * TODO: make an array of uniforms that the user will set
		 * when they create a shader.
		 */
		GLint uniformTexture;
		GLint uniformMVP;
	};
}

//==============================================================================
// ALI STUFF
//==============================================================================
/*glm::vec4 light_position(2.0, 0.0, 0.0, 0.0);
glm::vec4 light_ambient(0.2, 0.2, 0.2, 1.0);
glm::vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
glm::vec4 light_specular(1.0, 1.0, 1.0, 1.0);

glm::vec4 material_ambient(1.0, 0.0, 1.0, 1.0);
glm::vec4 material_diffuse(1.0, 0.8, 0.0, 1.0);
glm::vec4 material_specular(1.0, 0.8, 0.0, 1.0);
float  material_shininess = 100.0;

glm::vec4 ambient_product = light_ambient * material_ambient;
glm::vec4 diffuse_product = light_diffuse * material_diffuse;
glm::vec4 specular_product = light_specular * material_specular;

glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
1, glm::value_ptr(ambient_product));
glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
1, glm::value_ptr(diffuse_product));
glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
1, glm::value_ptr(specular_product));
glUniform4fv(glGetUniformLocation(program, "LightPosition"),
1, glm::value_ptr(light_position));

glUniform1f(glGetUniformLocation(program, "Shininess"),
material_shininess);*/
