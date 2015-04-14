#include "MeshShader.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include "Scene.h"

#define MODEL_VIEW "modelview"
#define PROJECTION "projection"
#define LOCAL_TO_WORLD "localToWorld"
#define CAMERA_POSITION "cameraPosition"
#define ROTATION "rotation"
#define CALCULATE_SPECULAR "calculateSpecular"

MeshShader::MeshShader()
{
}

MeshShader::~MeshShader()
{
}

void MeshShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader )
{
	CreateShaderProgram();

	if (vertexShader != nullptr)
	{
		AttachAndCompileShaderFromFile(vertexShader, EShaderType::SHADER_VERTEX);
	}
	if (fragmentShader != nullptr)
	{
		AttachAndCompileShaderFromFile(fragmentShader, EShaderType::SHADER_FRAGMENT);
	}
	
	BuildShaderProgram();

	// Get locations
	m_uniforms.modelview = glGetUniformLocation(GetProgramHandle(), MODEL_VIEW);
	m_uniforms.projection = glGetUniformLocation(GetProgramHandle(), PROJECTION);
	m_uniforms.localToWorld = glGetUniformLocation(GetProgramHandle(), LOCAL_TO_WORLD);
	m_uniforms.cameraPosition = glGetUniformLocation(GetProgramHandle(), CAMERA_POSITION);
	m_uniforms.rotation = glGetUniformLocation(GetProgramHandle(), ROTATION);
	m_uniforms.bCalculateSpecular = glGetUniformLocation(GetProgramHandle(), CALCULATE_SPECULAR);
}

void MeshShader::UpdateUniformValues(const MeshNodePtr pSceneNode, const CameraPtr pCamera) const
{
	if (pSceneNode)
	{
		ActorPtr pActor;

		if (pActor = pSceneNode->GetActor().lock())
		{
			glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(pActor->GetComponent<Transform>()->GetTransformation()));
			glUniformMatrix4fv(m_uniforms.rotation, 1, GL_FALSE, glm::value_ptr(pActor->GetComponent<Transform>()->GetOrientation()));

			glUniform1i(m_uniforms.bCalculateSpecular, pSceneNode->GetCalculateSpecular());
		}
	}
	if (pCamera)
	{
		glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
		glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));

		glUniform3f(m_uniforms.cameraPosition, 1, GL_FALSE, *glm::value_ptr(pCamera->GetOwner()->GetComponent<Transform>()->GetPosition()));
	}
}

void MeshShader::PreRender()
{
	ActivateShaderProgram();

	UpdateUniformValues(nullptr, Scene::GetCamera());
}