#include "SkyBoxShader.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include "Scene.h"

#define MODEL_VIEW "modelview"
#define PROJECTION "projection"
#define LOCAL_TO_WORLD "localToWorld"
#define DAY_AND_NIGHT "dayAndNight"

SkyBoxShader::SkyBoxShader()
{
}

SkyBoxShader::~SkyBoxShader()
{
}

void SkyBoxShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader)
{
	CreateShaderProgram();

	AttachAndCompileShaderFromFile(vertexShader, EShaderType::SHADER_VERTEX);
	AttachAndCompileShaderFromFile(fragmentShader, EShaderType::SHADER_FRAGMENT);

	BuildShaderProgram();

	// Get locations
	m_uniforms.modelview = glGetUniformLocation(GetProgramHandle(), MODEL_VIEW);
	m_uniforms.projection = glGetUniformLocation(GetProgramHandle(), PROJECTION);
	m_uniforms.localToWorld = glGetUniformLocation(GetProgramHandle(), LOCAL_TO_WORLD);
	m_uniforms.dayAndNight = glGetUniformLocation(GetProgramHandle(), DAY_AND_NIGHT);

}

void SkyBoxShader::UpdateUniformValues(const SkyBoxNodePtr pSceneNode) const
{
	pSceneNode->PreRender();

	// Pass in local to world matrix
	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetTransformation()));
}

void SkyBoxShader::PreRender(const CameraPtr pCamera, glm::vec4& dayAndNight)
{
	ActivateShaderProgram();

	// Pass in camera modelview and project matrices
	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));

	// Pass in ambient light
	glUniform4fv(m_uniforms.dayAndNight, 1, glm::value_ptr(dayAndNight));
}