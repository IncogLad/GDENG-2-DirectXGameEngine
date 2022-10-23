#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"

#include <d3dcompiler.h>

#include "RenderTexture.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance!=NULL)
	{
		sharedInstance->release();
	}
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	

	return true;
}


bool GraphicsEngine::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();

	m_d3d_device->Release();

	m_RenderTexture->Shutdown();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}


DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::createRenderTexture( int textureWidth, int textureHeight)
{
	bool result;
	this->m_RenderTexture = new RenderTexture();

	result = this->m_RenderTexture->Initialize(this->m_d3d_device, textureWidth, textureHeight);
	if (!result)
	{
		return false;
	}

	return result;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

//bool GraphicsEngine::Render()
//{
	//bool result;

	//// Render the entire scene to the texture first.
	//result = RenderToTexture();
	//if (!result)
	//{
	//	return false;
	//}

	//// Clear the buffers to begin the scene.
	//m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	//BeginScene = ...
	//{
	//	float color[4];
	//	// Setup the color to clear the buffer to.
	//	color[0] = red;
	//	color[1] = green;
	//	color[2] = blue;
	//	color[3] = alpha;

	//	// Clear the back buffer.
	//	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	//	// Clear the depth buffer.
	//	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//}

	//// Render the scene as normal to the back buffer.
	//result = RenderScene();
	//if (!result)
	//{
	//	return false;
	//}
//}

void GraphicsEngine::RenderToTexture(SwapChain* swap_chain)
{

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(sharedInstance->m_imm_context, swap_chain->getDepthStencilView());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(sharedInstance->m_imm_context, swap_chain->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	//result = RenderScene();
	//if (!result)
	//{
	//	return false;
	//}
}

void GraphicsEngine::SetBackBufferRenderTarget(SwapChain* swap_chain)
{
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	//m_D3D->SetBackBufferRenderTarget(); =...
	sharedInstance->m_imm_context->OMSetRenderTargets(1, &swap_chain->m_rtv, swap_chain->getDepthStencilView());
}

RenderTexture* GraphicsEngine::getRenderedTexture()
{
	return this->m_RenderTexture;
}

//bool GraphicsEngine::RenderScene()
//{
	//D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//bool result;
	//static float rotation = 0.0f;


	//// Generate the view matrix based on the camera's position.
	//m_Camera->Render();

	//// Get the world, view, and projection matrices from the camera and d3d objects.
	//m_D3D->GetWorldMatrix(worldMatrix);
	//m_Camera->GetViewMatrix(viewMatrix);
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	//// Update the rotation variable each frame.
	//rotation += (float)D3DX_PI * 0.005f;
	//if (rotation > 360.0f)
	//{
	//	rotation -= 360.0f;
	//}

	//// Multiply the world matrix by the rotation.
	//D3DXMatrixRotationY(&worldMatrix, rotation);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// Render the model with the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	//return true;
//}


