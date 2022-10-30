#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "InputListener.h"
#include "Matrix4x4.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera();
	~Camera();

	void initialize(std::string name) override;
	void destroy() override;

	void draw(VertexShader* m_vs, PixelShader* m_ps) override;

	void update(float deltaTime);

	Matrix4x4 getViewMatrix();

	//KEYBOARD pure virtual callback functions 
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	//MOUSE pure virtual callback functions
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;
private:
	

	Matrix4x4 worldCam;
	Vector3D camPos;

	Camera(Camera const&) {}
	Camera& operator=(Camera const&) {}


};
