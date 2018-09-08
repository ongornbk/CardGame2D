#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"

namespace
{
	GameRenderer* m_instance = nullptr;

	static void _stdcall renderFoo() noexcept
	{
		m_instance->Render();
	}
}

GameRenderer::GameRenderer() : RendererManager(&renderFoo)
{
	m_instance = this;
}


GameRenderer::~GameRenderer()
{
}

void GameRenderer::Update()
{
}

void GameRenderer::Render()
{
	SetBrush(m_cornflowerBlueBrush);
	for (int x = 0; x < m_renderTargetSize.x; x += 10)
		DrawLine({ (float)x,m_renderTargetSize.y }, { (float)x,0 });
	SetBrush(m_lightSlateGrayBrush);
	for (int y = 0; y < m_renderTargetSize.y; y += 10)
		DrawLine({0.0f,(float)y }, { m_renderTargetSize.x,(float)y });
}
