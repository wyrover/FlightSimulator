#include "SkyBoxShader.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include "Scene.h"

#define MODEL_VIEW "modelview"
#define PROJECTION "projection"
#define LOCAL_TO_WORLD "localToWorld"

SkyBoxShader::SkyBoxShader()
{
}

SkyBoxShader::~SkyBoxShader()
{
}

void SkyBoxShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader)
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

}

void SkyBoxShader::UpdateUniformValues(const SkyBoxNodePtr pSceneNode) const
{
	pSceneNode->PreRender();

	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetTransformation()));
}

void SkyBoxShader::PreRender(const CameraPtr pCamera)
{
	ActivateShaderProgram();

	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));
}