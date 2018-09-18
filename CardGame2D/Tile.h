#pragma once
#include <DirectXMath.h>

#define GAMEMAP_SIZEX 1024
#define GAMEMAP_SIZEY 50

struct Tile
{
	Tile() = default;
	~Tile() = default;

	DirectX::XMFLOAT2 position;
	void* m_brush;
};