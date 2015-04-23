#pragma once
#include "GLSLShader.h"
#include "Camera.h"
#include <memory>

class Billboard;
class BillboardShader;

typedef std::shared_ptr<BillboardShader> BillboardShaderPtr;
typedef std::shared_ptr<Billboard> BillboardPtr;

class BillboardShader : public GLSLShaderProgram
{
private:
	struct Uniforms
	{
		int modelview, projection, localToWorld;
	};

	Uniforms				m_uniforms;

	glm::vec3				m_cameraPosition;

public:
	BillboardShader();
	virtual ~BillboardShader();

	const Uniforms			GetUniforms() const
	{
		return m_uniforms;
	}

	void					PreRender(const CameraPtr pCamera);

	inline void				PostRender()
	{
		DeactivateShaderProgram();
	}

	void					AttachAndBuildProgram(const LPWSTR vertexShader = nullptr, const LPWSTR fragmentShader = nullptr);
	void					UpdateUniformValues(const BillboardPtr pBillboard) const;
};

