#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Renderer.h"

class AppWindow : public Window
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
private:
	static AppWindow* sharedInstance;

	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

	//VertexBuffer* m_vb;
	//ConstantBuffer* m_cb;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};
