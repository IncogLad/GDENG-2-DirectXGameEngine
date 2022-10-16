#pragma once
#include <iostream>
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

class Cube : public AGameObject
{
public:
	Cube();
	~Cube();

	void initialize() override;
	void destroy() override;

	void initBuffers(void* shader_byte_code, size_t size_shader);
	void initConstBuffers();
	void draw(VertexShader* m_vs, PixelShader* m_ps) override;
	void releaseBuffers();

	void updatePosition();

private:
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	constant cc;
	double speed = 2;
	bool decrease = false;

	float m_delta_pos;
	float m_delta_scale;

	Cube(Cube const&) {}
	Cube& operator=(Cube const&) {}

};
