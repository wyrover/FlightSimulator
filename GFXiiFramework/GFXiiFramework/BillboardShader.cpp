#include "BillboardShader.h"
#include "Billboard.h"
#include "GLEW\include\glew.h"
#include "glm\gtc\type_ptr.hpp"

#define MODEL_VIEW "modelview"
#define PROJECTION "projection"
#define LOCAL_TO_WORLD "localToWorld"

BillboardShader::BillboardShader()
{
}

BillboardShader::~BillboardShader()
{
}

void BillboardShader::AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader)
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

void BillboardShader::UpdateUniformValues(const BillboardPtr pBillboard) const
{
	TransformPtr pTransform = pBillboard->GetComponent<Transform>();

	glm::vec4 n = glm::vec4(glm::normalize(m_cameraPosition - pTransform->GetPosition()), 0);
	glm::vec4 u = glm::vec4(0, 1, 0, 0);
	glm::vec4 r = glm::vec4((glm::cross(glm::vec3(u), glm::vec3(n))), 0);
	glm::vec4 pos = glm::vec4(pTransform->GetPosition(), 1);

	glm::mat4 mat(r, u, n, pos);

	glUniformMatrix4fv(m_uniforms.localToWorld, 1, GL_FALSE, glm::value_ptr(mat));
}

void BillboardShader::PreRender(const CameraPtr pCamera)
{
	ActivateShaderProgram();

	glUniformMatrix4fv(m_uniforms.modelview, 1, GL_FALSE, glm::value_ptr(pCamera->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniforms.projection, 1, GL_FALSE, glm::value_ptr(pCamera->GetProjectionMat4()));

	m_cameraPosition = pCamera->GetPosition();
}