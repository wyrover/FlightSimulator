#include "Matrix4x4.h"
#include <math.h>

#define RADIANS 3.14159265359 / 180.0

Matrix4x4::Matrix4x4()
{
	SetIdentityMatrix();
}

Matrix4x4::Matrix4x4(float matrix[4][4])
{
	for (unsigned row = 0; row < 4; row++)
	{
		for (unsigned column = 0; column < 4; column++)
		{
			m_matrix[row][column] = matrix[row][column];
		}
	}
}

Matrix4x4::~Matrix4x4()
{
}

// Reset matrix
void Matrix4x4::SetIdentityMatrix()
{
	for (unsigned row = 0; row < 4; row++)
	{
		for (unsigned column = 0; column < 4; column++)
		{
			if (row == column)
				m_matrix[row][column] = 1;
			else
				m_matrix[row][column] = 0;
		}
	}
}

void Matrix4x4::SetMatrix(const Matrix4x4 &mat)
{
	for (unsigned row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			m_matrix[row][column] = mat.GetValue(row, column);
		}
	}
}

void Matrix4x4::SetRotationX(const float rotationX)
{
	SetIdentityMatrix();

	m_matrix[1][1] = cos(rotationX * RADIANS);
	m_matrix[1][2] = -sin(rotationX * RADIANS);
	m_matrix[2][1] = sin(rotationX * RADIANS);
	m_matrix[2][2] = cos(rotationX * RADIANS);
}

void Matrix4x4::SetRotationY(const float rotationY)
{
	SetIdentityMatrix();

	m_matrix[0][0] = cos(rotationY * RADIANS);
	m_matrix[0][2] = sin(rotationY * RADIANS);
	m_matrix[2][0] = -sin(rotationY * RADIANS);
	m_matrix[2][2] = cos(rotationY * RADIANS);
}

void Matrix4x4::SetRotationZ(const float rotationZ)
{
	SetIdentityMatrix();

	m_matrix[0][0] = cos(rotationZ * RADIANS);
	m_matrix[0][1] = -sin(rotationZ * RADIANS);
	m_matrix[1][0] = sin(rotationZ * RADIANS);
	m_matrix[1][1] = cos(rotationZ * RADIANS);
}

void Matrix4x4::SetRotation(const Vector3 rotation)
{
	SetIdentityMatrix();

	if (rotation.GetX() == 0)
	{
		m_matrix[1][1] = cos(rotation.GetY() * RADIANS);
		m_matrix[1][2] = -sin(rotation.GetY() * RADIANS);
		m_matrix[2][1] = sin(rotation.GetZ() * RADIANS);
		m_matrix[2][2] = cos(rotation.GetZ() * RADIANS);
	}
	else if (rotation.GetY() == 0)
	{
		m_matrix[0][0] = cos(rotation.GetX() * RADIANS);
		m_matrix[0][2] = sin(rotation.GetX() * RADIANS);
		m_matrix[2][0] = -sin(rotation.GetZ() * RADIANS);
		m_matrix[2][2] = cos(rotation.GetZ() * RADIANS);
	}
	else
	{
		m_matrix[0][0] = cos(rotation.GetX() * RADIANS);
		m_matrix[0][1] = -sin(rotation.GetX() * RADIANS);
		m_matrix[1][0] = sin(rotation.GetY() * RADIANS);
		m_matrix[1][1] = cos(rotation.GetY() * RADIANS);
	}
}

void Matrix4x4::SetScale(const Vector3 scale)
{
	SetIdentityMatrix();

	m_matrix[0][0] = scale.GetX();
	m_matrix[1][1] = scale.GetY();
	m_matrix[2][2] = scale.GetZ();
}

void Matrix4x4::SetTranslation(const Vector3 translation)
{
	SetIdentityMatrix();

	m_matrix[0][3] = translation.GetX();
	m_matrix[1][3] = translation.GetY();
	m_matrix[2][3] = translation.GetZ();
}

const Vector3 Matrix4x4::operator*(const Vector3 &rhs) const
{
	//Calculate x prime
	float xprime = (m_matrix[0][0] * rhs.GetX()) + (m_matrix[0][1] * rhs.GetY()) + (m_matrix[0][2] * rhs.GetZ()) + (m_matrix[0][3] * rhs.GetW());

	//Calculate y prime
	float yprime = (m_matrix[1][0] * rhs.GetX()) + (m_matrix[1][1] * rhs.GetY()) + (m_matrix[1][2] * rhs.GetZ()) + (m_matrix[1][3] * rhs.GetW());

	//Calculate z prime
	float zprime = (m_matrix[2][0] * rhs.GetX()) + (m_matrix[2][1] * rhs.GetY()) + (m_matrix[2][2] * rhs.GetZ()) + (m_matrix[2][3] * rhs.GetW());

	return Vector3(xprime, yprime, zprime);
}

const Matrix4x4	Matrix4x4::operator*(Matrix4x4 &rhs) const
{
	Matrix4x4 result;

	// Row 0 Column 0
	result.m_matrix[0][0] = (m_matrix[0][0] * rhs.GetValue(0, 0)) + (m_matrix[0][1] * rhs.GetValue(1, 0)) + (m_matrix[0][2] * rhs.GetValue(2, 0)) + (m_matrix[0][3] * rhs.GetValue(3, 0));

	// Row 0 Column 1
	result.m_matrix[0][1] = (m_matrix[0][0] * rhs.GetValue(0, 1)) + (m_matrix[0][1] * rhs.GetValue(1, 1)) + (m_matrix[0][2] * rhs.GetValue(2, 1)) + (m_matrix[0][3] * rhs.GetValue(3, 1));

	// Row 0 Column 2
	result.m_matrix[0][2] = (m_matrix[0][0] * rhs.GetValue(0, 2)) + (m_matrix[0][1] * rhs.GetValue(1, 2)) + (m_matrix[0][2] * rhs.GetValue(2, 2)) + (m_matrix[0][3] * rhs.GetValue(3, 2));

	// Row 0 Column 3
	result.m_matrix[0][3] = (m_matrix[0][0] * rhs.GetValue(0, 3)) + (m_matrix[0][1] * rhs.GetValue(1, 3)) + (m_matrix[0][2] * rhs.GetValue(2, 3)) + (m_matrix[0][3] * rhs.GetValue(3, 3));



	// Row 1 Column 0
	result.m_matrix[1][0] = (m_matrix[1][0] * rhs.GetValue(0, 0)) + (m_matrix[1][1] * rhs.GetValue(1, 0)) + (m_matrix[1][2] * rhs.GetValue(2, 0)) + (m_matrix[1][3] * rhs.GetValue(3, 0));

	// Row 1 Column 1
	result.m_matrix[1][1] = (m_matrix[1][0] * rhs.GetValue(0, 1)) + (m_matrix[1][1] * rhs.GetValue(1, 1)) + (m_matrix[1][2] * rhs.GetValue(2, 1)) + (m_matrix[1][3] * rhs.GetValue(3, 1));

	// Row 1 Column 2
	result.m_matrix[1][2] = (m_matrix[1][0] * rhs.GetValue(0, 2)) + (m_matrix[1][1] * rhs.GetValue(1, 2)) + (m_matrix[1][2] * rhs.GetValue(2, 2)) + (m_matrix[1][3] * rhs.GetValue(3, 2));

	// Row 1 Column 3
	result.m_matrix[1][3] = (m_matrix[1][0] * rhs.GetValue(0, 3)) + (m_matrix[1][1] * rhs.GetValue(1, 3)) + (m_matrix[1][2] * rhs.GetValue(2, 3)) + (m_matrix[1][3] * rhs.GetValue(3, 3));



	// Row 2 Column 0
	result.m_matrix[2][0] = (m_matrix[2][0] * rhs.GetValue(0, 0)) + (m_matrix[2][1] * rhs.GetValue(1, 0)) + (m_matrix[2][2] * rhs.GetValue(2, 0)) + (m_matrix[2][3] * rhs.GetValue(3, 0));

	// Row 2 Column 1
	result.m_matrix[2][1] = (m_matrix[2][0] * rhs.GetValue(0, 1)) + (m_matrix[2][1] * rhs.GetValue(1, 1)) + (m_matrix[2][2] * rhs.GetValue(2, 1)) + (m_matrix[2][3] * rhs.GetValue(3, 1));

	// Row 2 Column 2
	result.m_matrix[2][2] = (m_matrix[2][0] * rhs.GetValue(0, 2)) + (m_matrix[2][1] * rhs.GetValue(1, 2)) + (m_matrix[2][2] * rhs.GetValue(2, 2)) + (m_matrix[2][3] * rhs.GetValue(3, 2));

	// Row 2 Column 3
	result.m_matrix[2][3] = (m_matrix[2][0] * rhs.GetValue(0, 3)) + (m_matrix[2][1] * rhs.GetValue(1, 3)) + (m_matrix[2][2] * rhs.GetValue(2, 3)) + (m_matrix[2][3] * rhs.GetValue(3, 3));



	// Row 3 Column 0
	result.m_matrix[3][0] = (m_matrix[3][0] * rhs.GetValue(0, 0)) + (m_matrix[3][1] * rhs.GetValue(1, 0)) + (m_matrix[3][2] * rhs.GetValue(2, 0)) + (m_matrix[3][3] * rhs.GetValue(3, 0));

	// Row 3 Column 1
	result.m_matrix[3][1] = (m_matrix[3][0] * rhs.GetValue(0, 1)) + (m_matrix[3][1] * rhs.GetValue(1, 1)) + (m_matrix[3][2] * rhs.GetValue(2, 1)) + (m_matrix[3][3] * rhs.GetValue(3, 1));

	// Row 3 Column 2
	result.m_matrix[3][2] = (m_matrix[3][0] * rhs.GetValue(0, 2)) + (m_matrix[3][1] * rhs.GetValue(1, 2)) + (m_matrix[3][2] * rhs.GetValue(2, 2)) + (m_matrix[3][3] * rhs.GetValue(3, 2));

	// Row 3 Column 3
	result.m_matrix[3][3] = (m_matrix[3][0] * rhs.GetValue(0, 3)) + (m_matrix[3][1] * rhs.GetValue(1, 3)) + (m_matrix[3][2] * rhs.GetValue(2, 3)) + (m_matrix[3][3] * rhs.GetValue(3, 3));

	return result;
}