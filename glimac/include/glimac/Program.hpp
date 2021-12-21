#pragma once

#include <GL/glew.h>
#include "Shader.hpp"
#include "FilePath.hpp"
#include "FreeflyCamera.hpp"
#include "SpotLight.hpp"

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
			uCameraPos = glGetUniformLocation(m_nGLId, "uCameraPos");
			uCameraLight = glGetUniformLocation(m_nGLId, "uCameraLight");
			uRodLight = glGetUniformLocation(m_nGLId, "uRodLight");
			uRoomLights = glGetUniformLocation(m_nGLId, "uRoomLights");
			uRodPos = glGetUniformLocation(m_nGLId, "uRodPos");
			uCameraDir = glGetUniformLocation(m_nGLId, "uCameraDir");
			uRodDir = glGetUniformLocation(m_nGLId, "uRodDir");
			uRoomPos = glGetUniformLocation(m_nGLId, "uRoomPos");
		}

		void updateLights(FreeflyCamera &camera, const glm::mat4 &treeMatrix, float mid)
		{
			cameraSpotLight.position = glm::vec4(camera.getPosition(), 1);
			cameraSpotLight.direction = glm::vec4(camera.getFrontVector(), 0);
			rodSpotLight.position = glm::translate(glm::mat4(1), glm::vec3(-mid, 5, 0)) * treeMatrix * glm::vec4(0, 0, 0, 1);
			rodSpotLight.direction = treeMatrix * glm::vec4(0, 0, 0, 1) - rodSpotLight.position;
		}

		void updateUniforms(FreeflyCamera &camera, glm::mat4 &objectMatrix)
		{
			glUniform1i(uCameraLight, cameraLight);
			glUniform1i(uRoomLights, roomLights);
			glUniform1i(uRodLight, rodLight);

			glm::mat4 viewMatrix = camera.getViewMatrix();
			glm::vec4 cameraPos = viewMatrix * cameraSpotLight.position;
			glUniform3f(uCameraPos, cameraPos.x, cameraPos.y, cameraPos.z);
			glm::vec4 newRodPos = viewMatrix * rodSpotLight.position;
			glUniform3f(uRodPos, newRodPos.x, newRodPos.y, newRodPos.z);
			glm::vec4 cameraDir = viewMatrix * cameraSpotLight.direction;
			glUniform3f(uCameraDir, cameraDir.x, cameraDir.y, cameraDir.z);
			glm::vec4 rodDir = viewMatrix * rodSpotLight.direction;
			glUniform3f(uRodDir, rodDir.x, rodDir.y, rodDir.z);
			glm::vec4 roomLigthPos = viewMatrix * glm::vec4(0, 10, 0, 1);
			glUniform3f(uRoomPos, roomLigthPos.x, roomLigthPos.y, roomLigthPos.z);

			viewMatrix = viewMatrix * objectMatrix;
			glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE,
							   glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE,
							   glm::value_ptr(glm::transpose(glm::inverse(viewMatrix))));
			glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE,
							   glm::value_ptr(projectionMatrix * viewMatrix));
		}

		void onOffCameraLight()
		{
			cameraLight = !cameraLight;
		}

		void onOffRodLight()
		{
			rodLight = !rodLight;
		}

		void onOffRoomLight()
		{
			roomLights = !roomLights;
		}

	private:
		Program(const Program &);
		Program &operator=(const Program &);

		GLuint m_nGLId;
		GLuint uProjectionMatrix;
		GLuint uViewMatrix;
		GLuint uNormalMatrix;
		GLuint uCameraPos;
		GLuint uRodPos;
		GLuint uRoomPos;
		GLuint uCameraLight;
		GLuint uRodLight;
		GLuint uRoomLights;
		GLuint uCameraDir;
		GLuint uRodDir;
		SpotLight cameraSpotLight;
		SpotLight rodSpotLight;
		bool cameraLight = true;
		bool rodLight = true;
		bool roomLights = true;
	};

	// Build a GLSL program from source code
	Program buildProgram(const GLchar *vsSrc, const GLchar *fsSrc);

	// Load source code from files and build a GLSL program
	Program loadProgram(const FilePath &vsFile, const FilePath &fsFile);

}
