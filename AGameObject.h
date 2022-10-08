#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

class AGameObject
{
public:
	virtual void initialize();
	virtual void destroy();

	virtual void draw(VertexShader* m_vs, PixelShader* m_ps) ;
};

