#include "Billboard.h"
#include "Material.h"
#include "Actor.h"
#include "GLEW\include\glew.h"

void Billboard::Init()
{
	SimpleVertex corners[] =
	{
		{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },// 0
		{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }, // 1
		{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f }, // 2
		{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, // 3
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SimpleVertex), corners, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(NULL + 12));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(NULL + 24));
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &m_vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Billboard::Render()
{
	unsigned int textureHandle = GetComponent<Material>()->GetDiffuse()->m_syshandle;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}