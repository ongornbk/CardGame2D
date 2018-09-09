#include "stdafx.h"
#include "TextureManagerMap.h"
#include "Texture.h"
#include <unordered_map>
#include <string>

namespace
{

	static std::unordered_map<std::wstring, Texture*> m_textures;
}

Boolean TextureManagerMap::PushTexture(std::wstring name,Texture * texture)
{
	if (m_textures.count(name))
	{
		return false;
	}
	else
	{
		m_textures[name] = texture;
		return true;
	}

}

Texture* TextureManagerMap::GetTexture(std::wstring name)
{
	if (m_textures.count(name))
	{
		return m_textures[name];
	}
	else
	{
		return nullptr;
	}
}

Boolean TextureManagerMap::ReleaseTextures()
{
	for (auto && ele : m_textures)
	{
		delete ele.second;
		ele.second = nullptr;
	}
	m_textures.clear();
	return true;
}
