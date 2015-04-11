#pragma once

#include "Listener.h"
#include "Texture.h"

class Cube
{
	protected:
		struct SimpleVertex
		{
				float position[3];
				float colour[3];
				float uv[2];
		};

		unsigned int	m_vao;
		unsigned int	m_vbo_verts;
		unsigned int	m_vbo_colours;
		unsigned int	m_vbo_indices;
				
		void			InitUnitCube();
		
	public:
						Cube();
						~Cube();
		

		void			Render();
};