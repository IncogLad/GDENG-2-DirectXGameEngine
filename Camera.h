#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"

class Camera : public AGameObject
{
public:
	Camera();
	~Camera();

	void initialize() override;
	void destroy() override;

	void draw(VertexShader* m_vs, PixelShader* m_ps) override;

	void update(ConstantBuffer* m_cb);

	void updatePosition();

private:
	constant cc;
	double speed = 2;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	Vector3D m_cam_pos;

	Camera(Camera const&) {}
	Camera& operator=(Camera const&) {}


};
