#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	//Initialize SwapChain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	//Release the swap chain
	bool release();

	ID3D11DepthStencilView* getDepthStencilView();
	ID3D11RenderTargetView* getRenderTargetView();

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	ID3D11BlendState* m_bs;

	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;

	ID3D11Texture2D* m_depthStencilBuffer;
private:
	friend class DeviceContext;
	friend class GraphicsEngine;
};
