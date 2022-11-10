#pragma once
#include "ResourceManager.h"
#include "Texture.h"


class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	Texture* createTextureFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};
