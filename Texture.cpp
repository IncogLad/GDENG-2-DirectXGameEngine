#include "Texture.h"
#include <DirectXTex.h>
#include <iostream>

#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	CoInitialize(nullptr);
	DirectX::ScratchImage *image_data = new DirectX::ScratchImage();
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, *image_data);

	res = DirectX::CreateTexture(GraphicsEngine::getInstance()->m_d3d_device, image_data->GetImages(),
		image_data->GetImageCount(), image_data->GetMetadata(), &m_texture);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::getInstance()->m_d3d_device, image_data->GetImages(),
			image_data->GetImageCount(), image_data->GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data->GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data->GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::getInstance()->m_d3d_device->CreateShaderResourceView(m_texture, &desc,
			&m_shader_res_view);

	}
	else
	{
		throw std::exception("Texture not created successfully");
	}

}


Texture::~Texture()
{
	m_shader_res_view->Release();
	m_texture->Release();
}

ID3D11ShaderResourceView* Texture::getShaderResourceView()
{
	return this->m_shader_res_view;
}

