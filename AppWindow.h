#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "InputListener.h"
#include "Renderer.h"

class AppWindow : public Window, public InputListener
{
public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	static AppWindow* sharedInstance;

	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube;

	constant cc;
	Matrix4x4 m_world_cam;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
};
