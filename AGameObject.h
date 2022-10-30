#pragma once
#include <string>

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


	virtual void initialize(std::string name);
	virtual void destroy();

	virtual void draw(VertexShader* m_vs, PixelShader* m_ps) ;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

private:

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;
};

