#pragma once
#include "Matrix4x4.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
};

struct vertexAnim
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

struct vertexCube
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16)) struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class AGameObject
{
public:


	virtual void initialize();
	virtual void destroy();

	virtual void draw(VertexShader* m_vs, PixelShader* m_ps) ;
};

