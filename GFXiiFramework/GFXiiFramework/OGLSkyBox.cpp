#include "OGLSkyBox.h"
#include "GLEW\include\glew.h"

OGLSkyBox::OGLSkyBox()
{
}

OGLSkyBox::~OGLSkyBox()
{
	delete[] m_textures;
}

void OGLSkyBox::Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom)
{
	OGLTexture frontTexture, backTexture, leftTexture, rightTexture, topTexture, bottomTexture;

	// Create textures
	frontTexture.CreateTextureFromFile(front);
	backTexture.CreateTextureFromFile(back);
	leftTexture.CreateTextureFromFile(left);
	rightTexture.CreateTextureFromFile(right);
	topTexture.CreateTextureFromFile(top);
	bottomTexture.CreateTextureFromFile(bottom);

	// Store textures

	m_textures[0] = frontTexture;
	m_textures[1] = backTexture;
	m_textures[2] = leftTexture;
	m_textures[3] = rightTexture;
	m_textures[4] = topTexture;
	m_textures[5] = bottomTexture;
}

void OGLSkyBox::Render() const
{
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_vao);

	// Back face
	glBindTexture(GL_TEXTURE_2D, m_textures[1].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)0);

	// Left face
	glBindTexture(GL_TEXTURE_2D, m_textures[2].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)24);

	// Front face
	glBindTexture(GL_TEXTURE_2D, m_textures[0].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)48);

	// Right face
	glBindTexture(GL_TEXTURE_2D, m_textures[3].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)72);

	// Bottom face
	glBindTexture(GL_TEXTURE_2D, m_textures[5].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)96);

	// Top face
	glBindTexture(GL_TEXTURE_2D, m_textures[4].m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)120);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}