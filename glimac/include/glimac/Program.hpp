#pragma once

#include <GL/glew.h>
#include "Shader.hpp"
#include "FilePath.hpp"
#include "FreeflyCamera.hpp"

namespace glimac
{

	const static glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);

	class Program
	{
	public:
		Program() : m_nGLId(glCreateProgram())
		{
		}

		~Program()
		{
			glDeleteProgram(m_nGLId);
		}

		Program(Program &&rvalue) : m_nGLId(rvalue.m_nGLId)
		{
			rvalue.m_nGLId = 0;
		}

		Program &operator=(Program &&rvalue)
		{
			m_nGLId = rvalue.m_nGLId;
			rvalue.m_nGLId = 0;
			return *this;
		}

		GLuint getGLId() const
		{
			return m_nGLId;
		}

		void attachShader(const Shader &shader)
		{
			glAttachShader(m_nGLId, shader.getGLId());
		}

		bool link();

		const std::string getInfoLog() const;

		void use()
		{
			glUseProgram(m_nGLId);
			uProjectionMatrix = glGetUniformLocation(m_nGLId, "uProjectionMatrix");
			uViewMatrix = glGetUniformLocation(m_nGLId, "uViewMatrix");
			uNormalMatrix = glGetUniformLocation(m_nGLId, "uNormalMatrix");
		}

		void updateMatrices(FreeflyCamera &camera, glm::mat4& objectMatrix)
		{
			glm::mat4 viewMatrix = camera.getViewMatrix();
			viewMatrix = viewMatrix * objectMatrix;
			glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE,
							   glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE,
							   glm::value_ptr(glm::transpose(glm::inverse(viewMatrix))));
			glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE,
							   glm::value_ptr(projectionMatrix * viewMatrix));
		}

	private:
		Program(const Program &);
		Program &operator=(const Program &);

		GLuint m_nGLId;
		GLuint uProjectionMatrix;
		GLuint uViewMatrix;
		GLuint uNormalMatrix;
	};

	// Build a GLSL program from source code
	Program buildProgram(const GLchar *vsSrc, const GLchar *fsSrc);

	// Load source code from files and build a GLSL program
	Program loadProgram(const FilePath &vsFile, const FilePath &fsFile);

}
