#pragma once
#include "ImageFactory.h"
#include "RenderTarget.h"
#include "d2d1.h"
#include "Types.h"
#include <string>
#include <DirectXMath.h>

class Texture : ImageFactory,RenderTarget
{
public:
	~Texture();
	Texture();
	Boolean CreateTextureFromFile(std::wstring name);

	void _vectorcall Draw(DirectX::XMFLOAT4 rect) noexcept;

private:
	IWICBitmapDecoder*     m_decoder;
	IWICBitmapFrameDecode* m_frame;
	IWICFormatConverter*   m_converter;
	IWICBitmapSource*      m_bitmapSource;
	ID2D1Bitmap*           m_bitmap;
	IWICBitmapScaler*      m_scaler;

	uint32_t m_width;
	uint32_t m_height;


};

