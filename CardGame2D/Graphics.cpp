#include "stdafx.h"
#include "Graphics.h"
#include "Direct2D.h"

#define gfx __f000__()->

Graphics::Graphics()
{
	m_activeBrush = m_cornflowerBlueBrush;
	m_stroke = 1.5f;
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
	gfx DrawLine( { pointA.x,pointA.y }, { pointB.x ,pointB.y}, m_activeBrush, m_stroke);

}

void Graphics::DrawRectangle(DirectX::XMFLOAT4 rectangle)
{
	gfx DrawRectangle({ rectangle.x,rectangle.y,rectangle.z,rectangle.w }, m_activeBrush,m_stroke);
}

void Graphics::FillRectangle(DirectX::XMFLOAT4 rectangle)
{
	gfx FillRectangle({ rectangle.x,rectangle.y,rectangle.z,rectangle.w }, m_activeBrush);
}

void Graphics::DrawEllipse(DirectX::XMFLOAT4 ellipse)
{
	gfx DrawEllipse({ ellipse.x,ellipse.y,ellipse.z,ellipse.w }, m_activeBrush, m_stroke);
}

void Graphics::DrawWideText(std::wstring text, DirectX::XMFLOAT4 rect)
{
	gfx DrawTextW(text.c_str(), (uint32_t)text.size(), m_textFormat, { rect.x,rect.y,rect.z,rect.w }, m_activeBrush);
}

void Graphics::SetStroke(float size)
{
	m_stroke = size;
}

void Graphics::SetTextSize(float size)
{
	m_textSize = size;
}

ID2D1HwndRenderTarget * Graphics::__f000__()
{
	return m_renderTarget.load();
}
