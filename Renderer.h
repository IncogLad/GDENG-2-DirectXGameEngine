#pragma once
#include <list>

#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quads.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static Renderer* getInstance();
	static void initialize();
	static void destroy();

	void initializeQuads(struct vertex list[], void* shader_byte_code, size_t size_shader);
	void insertQuads(class Quads* quad);
	void releaseQuads();
	std::list<class Quads*> getQuadList();
	
private:
	static Renderer* sharedInstance;
	std::list<class Quads*> vertexBufferList;

	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};
	

};

