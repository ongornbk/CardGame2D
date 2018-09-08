#pragma once
#include <DirectXMath.h>
#include <d2d1_2.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Types.h"

#pragma comment(lib,"d2d1.lib")

class Direct2D
{
public:
	Direct2D();
	~Direct2D();

	Boolean CreateFactory();
	Boolean InitializeResources();
	Boolean DiscardDeviceResources();
	Boolean OnResize(uint32_t width, uint32_t height);
	
	void BeginDraw();
	void EndDraw();

	friend class Framework;

protected:
	HWND m_hwnd;
	ID2D1Factory*          m_factory;
	ID2D1SolidColorBrush*  m_lightSlateGrayBrush;
	ID2D1SolidColorBrush*  m_cornflowerBlueBrush;
};

