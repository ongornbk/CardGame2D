#pragma once
#include "d2d1.h"
#include <DirectXMath.h>
#include "Brushes.h"
#include "RendererManager.h"
#include "RenderTarget.h"
#include "BitmapDecoder.h"
#include "TextFormat.h"
#include "ImageFactory.h"
#include "Types.h"


class Direct2D : Brushes,RenderTarget,RenderTargetSize,TextFormat,TextSize,ImageFactory,TextureManagerMap
{
public:
	Direct2D();
	~Direct2D();

	Boolean CreateFactory();
	Boolean InitializeResources();
	Boolean DiscardDeviceResources();
	Boolean OnResize(uint32_t width, uint32_t height);



	static void SetRendererManager(RendererManager* renderer);
	
	void BeginDraw();
	void EndDraw();

	friend class Framework;

protected:
	HWND m_hwnd;
	ID2D1Factory*          m_factory;
	IDWriteFactory*        m_writeFactory;

};

