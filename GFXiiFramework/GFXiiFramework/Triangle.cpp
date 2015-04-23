#include "Triangle.h"

Triangle::Triangle()
{
	
}

Triangle::Triangle(Vector3 pos1, Vector3 pos2, Vector3 pos3)
{
	SetVertices(pos1, pos2, pos3);
}


Triangle::~Triangle()
{
}

void Triangle::SetVertices(Vector3 v0, Vector3 v1, Vector3 v2)
{
	m_vertices[0].m_position = v0;
	m_vertices[1].m_position = v1;
	m_vertices[2].m_position = v2;
}

void Triangle::SetNormals(Vector3 n0, Vector3 n1, Vector3 n2)
{
	m_vertices[0].m_normal = n0;
	m_vertices[1].m_normal = n1;
	m_vertices[2].m_normal = n2;
}

void Triangle::SetTexCoords(Vector3 t0, Vector3 t1, Vector3 t2)
{
	m_vertices[0].m_texcoords = t0;
	m_vertices[1].m_texcoords = t1;
	m_vertices[2].m_texcoords = t2;
}

/*
	Resource: Mathematics for Computer Games Programming and Computer Graphics 3rd Edition
*/
void Triangle::GenerateTanget()
{
	const Vector3 v1 = m_vertices[0].m_position;
	const Vector3 v2 = m_vertices[1].m_position;
	const Vector3 v3 = m_vertices[2].m_position;

	const Vector3 w1 = m_vertices[0].m_texcoords;
	const Vector3 w2 = m_vertices[1].m_texcoords;
	const Vector3 w3 = m_vertices[2].m_texcoords;

	// x = 0, y = 1, z = 2

	// NO IDEA IF THIS IS F-ING RIGHT :-)
	float x1 = v2[0] - v1[0];
	float x2 = v3[0] - v1[0];

	float y1 = v2[1] - v1[1];
	float y2 = v3[1] - v1[1];

	float z1 = v2[2] - v1[2];
	float z2 = v3[2] - v1[2];

	float s1 = w2[0] - w1[0];
	float s2 = w3[0] - w1[0];
	float t1 = w2[1] - w1[1];
	float t2 = w3[1] - w1[1];

	float r = 1.0f / (s1 * t2 - s2 * t1);

	const Vector3 tangent((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);

	m_vertices[0].m_tangent = (tangent - m_vertices[0].m_normal * m_vertices[0].m_normal.DotProduct(tangent)).Normalise();
	m_vertices[1].m_tangent = (tangent - m_vertices[1].m_normal * m_vertices[1].m_normal.DotProduct(tangent)).Normalise();
	m_vertices[2].m_tangent = (tangent - m_vertices[2].m_normal * m_vertices[2].m_normal.DotProduct(tangent)).Normalise();
}