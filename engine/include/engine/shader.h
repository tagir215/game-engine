#pragma once
#include <string>
#include <glm/glm.hpp> 

class Shader {
public:
	Shader(const char* const vertexShaderString, const char* const fragmentShaderString);
	~Shader();

	void bind();
	void setUniform(const std::string& name, const glm::mat4& m);
	void setUniform(const std::string& name, float x, float y, float z, float w);
	void setUniform(const std::string& name, int value);
	GLuint getProgram() {
		return m_shaderProgram;
	}
private:
	GLuint m_shaderProgram;

};
