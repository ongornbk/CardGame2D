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
std::wstring w;
float tt = 200.0f;

void GameRenderer::Render()
{
	float stroke = 4.0f;
	SetBrush(m_lightSlateGrayBrush);
	SetStroke(stroke);
	DrawRectangle({ m_renderTargetSize.x-10.0f,m_renderTargetSize.y-10.0f,10.0f,10.0f });
	w += L"#";
	tt *= 0.999f;
	SetTextSize(tt);
	DrawWideText(w, { m_renderTargetSize.x, 100.0f,0.0f,10.0f });
}
