#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\quaternion.hpp"
#include <iostream>

#define TO_RADIANS(x) (float)(x * 3.14159265359 / 180.0)

int main()
{
	glm::mat4 rotX, rotY, rotZ;

	rotX[1][1] = cos(TO_RADIANS(90)); rotX[1][2] = -sin(TO_RADIANS(90));
	rotX[2][1] = sin(TO_RADIANS(90)); rotX[2][2] = cos(TO_RADIANS(90));

	rotY[0][0] = cos(TO_RADIANS(90)); rotY[0][2] = sin(TO_RADIANS(90));
	rotY[2][0] = -sin(TO_RADIANS(90)); rotY[2][2] = cos(TO_RADIANS(90));

	glm::vec4 point(0, 1, 0, 0);

	glm::vec4 result = rotY * rotX * point;

	return 0;
}