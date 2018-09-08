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

float mlt = 0.0f;
float addd = 0.05f;

void GameRenderer::Render()
{
	float stroke = 4.0f;
	SetBrush(m_lightSlateGrayBrush);
	SetStroke(stroke);
	DrawRectangle({ m_renderTargetSize.x-10.0f,m_renderTargetSize.y-10.0f,10.0f,10.0f });
	DrawWideText(L"Woll", { m_renderTargetSize.x, 100.0f,0.0f,10.0f });
}
