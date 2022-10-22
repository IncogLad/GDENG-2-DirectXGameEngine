#pragma once
#include <d3d11.h>

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

	ID3D11ShaderResourceView* getShaderResourceView();
	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	ID3D11ShaderResourceView* m_srv;
	ID3D11BlendState* m_bs;
private:
	friend class DeviceContext;
};
