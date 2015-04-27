#pragma once
#include "GLSLShader.h"
#include "SkyBoxNode.h"
#include "Camera.h"

class SkyBoxShader;

typedef std::shared_ptr<SkyBoxShader> SkyBoxShaderPtr;

class SkyBoxShader : public GLSLShaderProgram
{
private:
	struct Uniforms
	{
		int modelview, projection, localToWorld, dayAndNight;
	};

	Uniforms				m_uniforms;

public:
	SkyBoxShader();
	virtual					~SkyBoxShader();

	const Uniforms			GetUniforms() const
	{
		return m_uniforms;
	}

	void					PreRender(const CameraPtr pCamera, glm::vec4& dayAndNight);

	inline void				PostRender()
	{
		DeactivateShaderProgram();
	}

	void					AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader);
	void					UpdateUniformValues(const SkyBoxNodePtr pSceneNode) const;
};

