//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "glm\glm.hpp"
//#include "vector3d.h"
//#include "matrix4x4.h"

class Quaternion
{
	private:
		glm::vec3			m_vector;
		float				m_scalar;

	public:
							Quaternion();
							~Quaternion();

		const glm::vec3&	GetVector() const;
		const float			GetScalar() const;
		
		float				operator [] (int index);
		Quaternion			operator + (const Quaternion& rhs) const;
		Quaternion			operator * (const Quaternion& rhs) const;
		
		float				Norm();
		float				Norm_Sqr() const;
		void				Normalise();
		void				ConvertToRotationMatrix(glm::mat4* rot) const;
		void				SetQuaternion(float vx, float vy, float vz, float s);
		void				SetQuaternion(const glm::vec3& vec, float s);
};

#endif
