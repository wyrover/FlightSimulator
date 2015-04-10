#pragma once

#include "BaseTexture.h"
#include "Actor.h"

class GameObject : public Actor
{
	protected:
		BaseTexture				*m_dif;
		BaseTexture				*m_spec;
		
	public:

		//this is a pure virtual function
								GameObject() { m_dif = m_spec = 0; }
		virtual void			Render() = 0; 
		
		inline void				SetDiffuse( BaseTexture* dif )
		{
			m_dif = dif;
		}

		inline void				SetSpecular(BaseTexture* spec)
		{
			m_spec = spec;
		}
};