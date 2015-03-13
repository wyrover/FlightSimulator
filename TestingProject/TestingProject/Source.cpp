#include "quaternion.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\quaternion.hpp"
#include <iostream>

#define TO_RADIANS(x) (float)(x * 3.14159265359 / 180.0)

int main()
{
	glm::vec3 upVector(0, 1, 0);
	glm::vec3 rightVector(1, 0, 0);
	glm::vec3 directionVector(0, 0, -1);

	while (true)
	{
		//Quaternion quatYaw, quatYawConj, point;

		//point.SetQuaternion(rightVector, 0);
		//quatYaw.SetQuaternion(upVector * sin(TO_RADIANS(10.0 / 2.0)), cos(TO_RADIANS(10.0 / 2.0)));
		//quatYawConj.SetQuaternion(quatYaw.GetVector() * -1.f, quatYaw.GetScalar());

		//rightVector = (quatYaw * point * quatYawConj).GetVector();

		//directionVector = glm::cross(upVector, rightVector);

		//upVector = glm::vec3(0, 1, 0);
		//rightVector = glm::vec3(1, 0, 0);
		//directionVector = glm::vec3(0, 0, -1);

		glm::quat newQuatYaw;

		newQuatYaw = glm::quat(glm::vec3(0, TO_RADIANS(10.0 / 2.0), 0));

		rightVector = newQuatYaw * rightVector * glm::conjugate(newQuatYaw);
	}

	return 0;
}