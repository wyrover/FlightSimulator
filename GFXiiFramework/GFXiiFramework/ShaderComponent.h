#pragma once
#include "Actor.h"
#include "ActorComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GLSLShader.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"

class ShaderComponent;

typedef std::shared_ptr<ShaderComponent> ShaderComponentPtr;
typedef std::shared_ptr<GLSLShaderProgram> ShaderProgramPtr;

class ShaderComponent : public ActorComponent
{
private:
	ShaderProgramPtr					m_pShaderProgram;
	WeakCameraPtr						m_pWeakCamera;

	int									m_uniform_modelview;
	int									m_uniform_projection;
	int									m_uniform_local_to_world;
	int									m_uniform_camera_position;
	int									m_uniform_rotation;

public:
	ShaderComponent() 
	{ 
		m_pShaderProgram = std::make_shared<GLSLShaderProgram>();

		m_pShaderProgram->CreateShaderProgram();
	}

	virtual								~ShaderComponent() 
	{ 
		if (m_pShaderProgram)
		{
			m_pShaderProgram->DeleteShaderProgram();
		}
	}

	static const ActorComponentID		COMPONENT_ID = 6;

	inline virtual ActorComponentID		GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	inline void							EnableShaderProgram() const
	{
		m_pShaderProgram->ActivateShaderProgram();
	}

	inline void							DisableShaderProgram() const
	{
		m_pShaderProgram->DeactivateShaderProgram();
	}

	inline void							AddFragmentShader(LPCWSTR shader)
	{
		m_pShaderProgram->AttachAndCompileShaderFromFile(shader, EShaderType::SHADER_FRAGMENT);

		glBindFragDataLocation(m_pShaderProgram->GetProgramHandle(), 0, "outFrag");
	}

	inline void							AddVertexShader(LPCWSTR shader)
	{
		m_pShaderProgram->AttachAndCompileShaderFromFile(shader, EShaderType::SHADER_VERTEX);
	}

	inline void							BuildShaderProgram()
	{
		m_pShaderProgram->BuildShaderProgram();

		m_uniform_modelview = glGetUniformLocation(m_pShaderProgram->GetProgramHandle(), "modelview");
		m_uniform_projection = glGetUniformLocation(m_pShaderProgram->GetProgramHandle(), "projection");
		m_uniform_local_to_world = glGetUniformLocation(m_pShaderProgram->GetProgramHandle(), "localToWorld");
		m_uniform_camera_position = glGetUniformLocation(m_pShaderProgram->GetProgramHandle(), "cameraPosition");
		m_uniform_rotation = glGetUniformLocation(m_pShaderProgram->GetProgramHandle(), "rotation");
	}

	inline void							PreRender()
	{
		m_pShaderProgram->ActivateShaderProgram();

		glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_pOwner->GetComponent<TransformComponent>()->GetTransformation()));
		glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_pOwner->GetComponent<TransformComponent>()->GetOrientation()));

		CameraPtr pCamera;

		if (pCamera = m_pWeakCamera.lock())
		{
			glUniformMatrix4fv(m_uniform_modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
			glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));
			glUniform3f(m_uniform_camera_position, 1, GL_FALSE, *glm::value_ptr(pCamera->GetOwner()->GetComponent<TransformComponent>()->GetPosition()));
		}
	}

	inline void							PostRender()
	{
		m_pShaderProgram->DeactivateShaderProgram();
	}

	inline void							SetCamera(CameraPtr pCamera)
	{
		m_pWeakCamera = pCamera;
	}
};

