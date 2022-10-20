#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <iostream>

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::getInstance()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = GraphicsEngine::getInstance()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		return false;
	}

	//Get the back buffer color and create its render target view
	//--------------------------------
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	//DSV CREATION
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = device->CreateTexture2D(&descDepth, NULL, &buffer);

	device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	buffer->Release();


	//SRV CREATION
	D3D11_TEXTURE2D_DESC srDesc;
	ZeroMemory(&srDesc, sizeof(D3D11_TEXTURE2D_DESC));
	srDesc.Width = width;
	srDesc.Height = height;
	srDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	srDesc.Usage = D3D11_USAGE_DEFAULT;
	srDesc.SampleDesc.Count = 1;
	srDesc.SampleDesc.Quality = 0;
	srDesc.CPUAccessFlags = 0;
	srDesc.ArraySize = 1;
	srDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	srDesc.MiscFlags = 0;
	srDesc.MipLevels = 1;

	hr = device->CreateTexture2D(&srDesc, NULL, &buffer);
		
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = srDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(buffer, &srvDesc, &m_srv);
	buffer->Release();

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

ID3D11ShaderResourceView* SwapChain::getShaderResourceView()
{
	return this->m_srv;
}

SwapChain::~SwapChain()
{
}