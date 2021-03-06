#include "SkyBox.h"
#include "GLEW\include\glew.h"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom)
{
	for (TexturePtr &pTexture : m_textures)
	{
		pTexture = std::make_shared<Texture>();
	}

	m_textures[0]->CreateTextureFromFile(front);
	m_textures[1]->CreateTextureFromFile(back);
	m_textures[2]->CreateTextureFromFile(left);
	m_textures[3]->CreateTextureFromFile(right);
	m_textures[4]->CreateTextureFromFile(top);
	m_textures[5]->CreateTextureFromFile(bottom);
}

void SkyBox::Render() const
{
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_vao);

	// Back face
	glBindTexture(GL_TEXTURE_2D, m_textures[1]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)0);

	// Left face
	glBindTexture(GL_TEXTURE_2D, m_textures[2]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)24);

	// Front face
	glBindTexture(GL_TEXTURE_2D, m_textures[0]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)48);

	// Right face
	glBindTexture(GL_TEXTURE_2D, m_textures[3]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)72);

	// Bottom face
	glBindTexture(GL_TEXTURE_2D, m_textures[5]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)96);

	// Top face
	glBindTexture(GL_TEXTURE_2D, m_textures[4]->m_syshandle);
	glDrawRangeElements(GL_TRIANGLES, 0, 0, 6, GL_UNSIGNED_INT, (void*)120);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}