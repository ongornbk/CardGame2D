#include "stdafx.h"
#include "Framework.h"


Framework::Framework()
{
	m_graphics = new Direct2D();
	m_graphics->CreateFactory();
}


Framework::~Framework()
{
	if (m_graphics)
	{
		delete m_graphics;
		m_graphics = nullptr;
	}
}

Framework * Framework::CreateFramework()
{
	Framework* framework = new Framework();
	return framework;
}

void Framework::Render()
{
	m_graphics->BeginDraw();
	m_graphics->EndDraw();
}

void Framework::Resize(uint32_t width, uint32_t height)
{
	m_graphics->OnResize(width, height);
}

void Framework::SetWindow(HWND hwnd)
{
	m_graphics->m_hwnd = hwnd;
}