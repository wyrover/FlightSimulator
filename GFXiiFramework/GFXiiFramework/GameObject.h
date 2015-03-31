#pragma once

#include "BaseTexture.h"
#include "Object.h"

//This is an abstract class
//It cannot be instantiated without being inherited by a concrete class
class GameObject : public Object
{
	protected:
		BaseTexture				*m_tex;
		
	public:

		//this is a pure virtual function
								GameObject() { m_tex = 0; }
		virtual void			Render() = 0;
		
		inline void				SetTexture( BaseTexture* tex )
		{
			m_tex = tex;
		}
};