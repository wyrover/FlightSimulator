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
#define CALCULATE_NORMAL "calculateNormal"
#define DAY_AND_NIGHT "dayAndNight"

MeshShader::MeshShader()
{
}

MeshShader::~MeshShader()
{
}

void MeshShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader )
{
	CreateShaderProgram();

	AttachAndCompileShaderFromFile(vertexShader, EShaderType::SHADER_VERTEX);
	AttachAndCompileShaderFromFile(fragmentShader, EShaderType::SHADER_FRAGMENT);

	BuildShaderProgram();

	// Get locations
	m_uniforms.modelview = glGetUniformLocation(GetProgramHandle(), MODEL_VIEW);
	m_uniforms.projection = glGetUniformLocation(GetProgramHandle(), PROJECTION);
	m_uniforms.localToWorld = glGetUniformLocation(GetProgramHandle(), LOCAL_TO_WORLD);
	m_uniforms.cameraPosition = glGetUniformLocation(GetProgramHandle(), CAMERA_POSITION);
	m_uniforms.rotation = glGetUniformLocation(GetProgramHandle(), ROTATION);
	m_uniforms.bCalculateSpecular = glGetUniformLocation(GetProgramHandle(), CALCULATE_SPECULAR);
	m_uniforms.bCalculateNormal = glGetUniformLocation(GetProgramHandle(), CALCULATE_NORMAL);
	m_uniforms.dayAndNight = glGetUniformLocation(GetProgramHandle(), DAY_AND_NIGHT);
}

void MeshShader::UpdateUniformValues(const MeshNodePtr pSceneNode) const
{
	pSceneNode->PreRender();

	// Local to world matrix and rotation matrix
	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetTransformation()));
	glUniformMatrix4fv(m_uniforms.rotation, 1, GL_FALSE, glm::value_ptr(pSceneNode->GetComponent<Transform>()->GetOrientation()));

	// Bools on where the calculate specular/normals
	glUniform1i(m_uniforms.bCalculateSpecular, pSceneNode->GetCalculateSpecular());
	glUniform1i(m_uniforms.bCalculateNormal, pSceneNode->GetCalculateNormal());
}

void MeshShader::PreRender(CameraPtr pCamera, glm::vec4& dayAndNight)
{
	ActivateShaderProgram();

	// Pass in camera modelview, projection and position
	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));
	glUniform3fv(m_uniforms.cameraPosition, 1, glm::value_ptr(pCamera->GetPosition()));

	// Pass in ambient
	glUniform4fv(m_uniforms.dayAndNight, 1, glm::value_ptr(dayAndNight));
}