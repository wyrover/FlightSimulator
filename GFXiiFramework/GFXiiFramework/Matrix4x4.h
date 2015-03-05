#pragma once

#include "Vector3.h"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(float matrix[4][4]);
	~Matrix4x4();

	void					SetIdentityMatrix();

	void					SetRotationX(const float rotationX);
	void					SetRotationY(const float rotationY);
	void					SetRotationZ(const float rotationZ);

	void					SetRotation(const Vector3 rotation);
	void					SetScale(const Vector3 scale);
	void					SetTranslation(const Vector3 translation);
	
	void					SetMatrix(const Matrix4x4 &mat);

	const Vector3			operator*(const Vector3 &rhs) const;
	const Matrix4x4			operator*(Matrix4x4 &rhs) const;

	inline float			GetValue(int row, int column) const { return m_matrix[row][column]; }
	
private:
	float m_matrix[4][4];
};