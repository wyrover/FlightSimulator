#include "BillboardShader.h"
#include "Billboard.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include "Scene.h"

#define MODEL_VIEW "modelview"
#define PROJECTION "projection"
#define LOCAL_TO_WORLD "localToWorld"
#define DAY_AND_NIGHT "dayAndNight"

BillboardShader::BillboardShader()
{
}

BillboardShader::~BillboardShader()
{
}

void BillboardShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader)
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

void BillboardShader::UpdateUniformValues(const BillboardPtr pBillboard) const
{
	TransformPtr pTransform = pBillboard->GetComponent<Transform>();

	// Create an axis aligned billboard
	glm::vec4 n = glm::vec4(glm::normalize(m_cameraPosition - pTransform->GetPosition()), 0);
	glm::vec4 u = glm::vec4(0, 1, 0, 0);
	glm::vec4 r = glm::vec4((glm::cross(glm::vec3(u), glm::vec3(n))), 0);
	glm::vec4 pos = glm::vec4(pTransform->GetPosition(), 1);

	glm::mat4 mat(r, u, n, pos);

	// Pass in local to world matrix
	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(mat * pTransform->GetScale()));
}

void BillboardShader::PreRender(const CameraPtr pCamera, glm::vec4& dayAndNight)
{
	ActivateShaderProgram();

	// Pass in camera modelview and project matrixes
	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));

	// Pass in ambient light
	glUniform4fv(m_uniforms.dayAndNight, 1, glm::value_ptr(dayAndNight));

	m_cameraPosition = pCamera->GetPosition();
}