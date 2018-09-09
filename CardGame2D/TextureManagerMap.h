#pragma once
#include "Types.h"
#include "Texture.h"
#include <string>

class TextureManagerMap
{
protected:
	Boolean PushTexture(std::wstring name,Texture* texture);
	Texture* GetTexture(std::wstring name);
	Boolean ReleaseTextures();
};

