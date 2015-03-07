#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <iostream>

int main()
{
	float mat[16];

	for (unsigned index = 0; index < 16; index++)
	{
		if (index == 0 || index == 5 || index == 10 || index == 15)
			mat[index] = 1;
		else
			mat[index] = 0;
	}

	glm::mat4 matrix = glm::make_mat4(mat);

	unsigned index = 0;
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++)
		{
			std::cout << matrix[i][j];
		}
		std::cout << "\n";
	}

	return 0;
}