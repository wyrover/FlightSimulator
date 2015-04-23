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
#define LIGHT_POSITION "lightPosition"
#define LIGHT_COLOUR "lightColour"
#define CALCULATE_NORMAL "calculateNormal"

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
	m_uniforms.bCalculateNormal = glGetUniformLocation(GetProgramHandle(), CALCULATE_NORMAL);
	m_uniforms.lightColour = glGetUniformLocation(GetProgramHandle(), LIGHT_COLOUR);
	m_uniforms.lightPosition = glGetUniformLocation(GetProgramHandle(), LIGHT_POSITION);
}

void MeshShader::UpdateUniformValues(const MeshNodePtr pSceneNode) const
{
	pSceneNode->PreRender();

	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetTransformation()));
	glUniformMatrix4fv(m_uniforms.rotation, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetOrientation()));

	glUniform1i(m_uniforms.bCalculateSpecular, pSceneNode->GetCalculateSpecular());
	glUniform1i(m_uniforms.bCalculateNormal, pSceneNode->GetCalculateNormal());
}

void MeshShader::PreRender(CameraPtr pCamera, LightNodePtr pLight)
{
	ActivateShaderProgram();

	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));

	glUniform3fv(m_uniforms.cameraPosition, 1, glm::value_ptr(pCamera->GetPosition()));
	glUniform3fv(m_uniforms.lightColour, 1, glm::value_ptr(pLight->GetLightColour()));
	glUniform3fv(m_uniforms.lightPosition, 1, glm::value_ptr(pLight->GetComponent<Transform>()->GetPosition()));
}