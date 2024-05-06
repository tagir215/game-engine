#include "engine/graphics/shader.h"
#include <string>
#include <iostream>

int createShader(const char* const shaderSource, GLuint shaderType) {
	int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
	}
	return shader;
}


GLuint linkShaders(int vertexShader, int fragmentShader) {
	GLuint m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	int success;
	char infoLog[512];

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		printf("ERROR: Shader link failed: \"%s\"\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return m_shaderProgram;
}

Shader::Shader(const char* const vertexShaderString, const char* const fragmentShaderString) {
	int v_shader = createShader(vertexShaderString, GL_VERTEX_SHADER);
	int f_shader = createShader(fragmentShaderString, GL_FRAGMENT_SHADER);
	const GLchar* feedbackVaryings[] = { "transformedPosition" }; 
	glTransformFeedbackVaryings(m_shaderProgram, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
	m_shaderProgram = linkShaders(v_shader, f_shader);
}

void Shader::bind() {
	glUseProgram(m_shaderProgram);

}


void Shader::setUniform(const std::string& name, const glm::mat4& m) {
	GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
	if (loc < 0) {
		return; 
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::setUniform(const std::string& name, float x, float y, float z, float w) {
	GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
	if (loc < 0) {
		return;
	}
	glUniform4f(loc, x, y, z, w);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		glUniform3f(loc, x, y, z); 
	}

}

void Shader::setUniform(const std::string& name, int value) {
	GLint loc = glGetUniformLocation(m_shaderProgram, name.c_str());
	if (loc < 0) {
		return; 
	}
	glUniform1i(loc, value);
}


Shader::~Shader() {

}
