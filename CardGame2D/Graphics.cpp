#include "stdafx.h"
#include "Graphics.h"

#define gfx __f000__()->

Graphics::Graphics()
{
	m_activeBrush = m_cornflowerBlueBrush;
}

Graphics::~Graphics()
{
}

void Graphics::SetBrush(ID2D1SolidColorBrush * brush)
{
	m_activeBrush = brush;
}

void Graphics::DrawLine(DirectX::XMFLOAT2 pointA, DirectX::XMFLOAT2 pointB)
{
	gfx DrawLine( { pointA.x,pointA.y }, { pointB.x ,pointB.y}, m_activeBrush, 1.5f);

}

ID2D1HwndRenderTarget * Graphics::__f000__()
{
	return m_renderTarget.load();
}
