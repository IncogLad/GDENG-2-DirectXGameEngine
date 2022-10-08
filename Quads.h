#pragma once
#include <iostream>
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Renderer.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

struct vertexAnim
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16)) struct constant
{
	float m_angle;
};

class Quads : public AGameObject
{
public:
	Quads();
	~Quads();

	void initialize() override;
	void destroy() override;

	void initBuffers(struct vertex list[], void* shader_byte_code, size_t size_shader);
	void initAnimBuffers(struct vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initConstBuffers();
	void draw(VertexShader* m_vs, PixelShader* m_ps) override;
	void releaseBuffers();

private:
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;

	constant cc;
	double speed = 2;
	bool decrease = false;

	Quads(Quads const&) {}
	Quads& operator=(Quads const&) {}
	
};

