#pragma once
#include <iostream>
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class Quads
{
public:
	Quads(std::string name, void* sharedByteCode, size_t shaderSize);
	~Quads();

	static Quads* getInstance();
	static void initialize();
	static void destroy();

	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	
	Quads(Quads const&) {};
	Quads& operator=(Quads const&) {};
	static Quads* sharedInstance;
};

