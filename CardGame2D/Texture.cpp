#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
	m_converter = nullptr;
	m_decoder = nullptr;
	m_frame = nullptr;
	m_bitmap = nullptr;
	m_scaler = nullptr;
	m_width = 0u;
	m_height = 0u;
}

Texture::~Texture()
{
	if (m_converter)
	{
		m_converter->Release();
		m_converter = nullptr;
	}
	if (m_decoder)
	{
		m_decoder->Release();
		m_decoder = nullptr;
	}
	if (m_frame)
	{
		m_frame->Release();
		m_frame = nullptr;
	}
	if (m_bitmap)
	{
		m_bitmap->Release();
		m_bitmap = nullptr;
	}
	if (m_scaler)
	{
		m_scaler->Release();
		m_scaler = nullptr;
	}
}

Boolean Texture::CreateTextureFromFile(std::wstring name)
{
	Boolean result;

	result = m_imageFactory->CreateDecoderFromFilename(name.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &m_decoder);
	CheckBoolean(result);
	result = m_decoder->GetFrame(0, &m_frame);
	CheckBoolean(result);
	result = m_frame->GetThumbnail(&m_bitmapSource);
	CheckBoolean(result);
	result = m_imageFactory->CreateFormatConverter(&m_converter);
	CheckBoolean(result);
	result = m_converter->Initialize(m_frame,GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0.f,WICBitmapPaletteTypeCustom);
	CheckBoolean(result);
	result = m_imageFactory->CreateBitmapScaler(&m_scaler);
	CheckBoolean(result);
	result = m_frame->GetSize(&m_width, &m_height);
	CheckBoolean(result);
	result = m_scaler->Initialize(m_frame,m_width,m_height,WICBitmapInterpolationModeCubic);
	CheckBoolean(result);


	
	
	if (m_converter && !m_bitmap)
	{
		m_renderTarget.load()->CreateBitmapFromWicBitmap(m_bitmapSource,&m_bitmap);
	}


	return true;
}

void _vectorcall Texture::Draw(DirectX::XMFLOAT4 rect) noexcept
{
	return m_renderTarget.load()->DrawBitmap(m_bitmap, { rect.x,rect.y,rect.z,rect.w }, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, { rect.x,rect.y,rect.z,rect.w });
}
