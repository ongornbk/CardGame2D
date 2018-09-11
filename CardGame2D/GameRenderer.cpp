#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"
#include "Timer.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <codecvt>

namespace
{
	GameRenderer* m_instance = nullptr;

	static void _stdcall renderFoo() noexcept
	{
		m_instance->Render();
	}

	static void _stdcall updateFoo() noexcept
	{
		m_instance->Update();
	}
}

GameRenderer::GameRenderer() : RendererManager(&updateFoo,&renderFoo)
{
	m_instance = this;
}


GameRenderer::~GameRenderer()
{
}

namespace
{
	clock_t deltaTime = 0;
	uint32_t frames = 0;
	double  frameRate = 30;
	double  averageFrameTimeMilliseconds = 33.333;
	clock_t bf;
	clock_t ef;
	int __fps = 0;

	extern "C"
	{
		double clockToMilliseconds(clock_t ticks) noexcept {
			// units/(units/time) => time (seconds) * 1000 = milliseconds
			return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
		}
	}
}

void GameRenderer::Update()
{
	bf = clock();
	Timer::Update();
	float dt = Timer::GetDeltaTime()*200.0f;
	if (m_input->IsKeyDown(DIK_LEFT))
	{
		m_cameraPosition.x += dt;
	}
	if (m_input->IsKeyDown(DIK_RIGHT))
	{
		m_cameraPosition.x -= dt;
	}
	if (m_input->IsKeyDown(DIK_UP))
	{
		m_cameraPosition.y += dt;
	}
	if (m_input->IsKeyDown(DIK_DOWN))
	{
		m_cameraPosition.y -= dt;
	}
	float mapCentreX = m_xSize / 2.0f;
	float mapCentreY = m_ySize / 2.0f;
	int32_t xs = mapCentreX - (m_cameraPosition.x / 50.0f) - (m_renderTargetSize.x / 2.0f);
	int32_t ys = mapCentreY - (m_cameraPosition.y / 50.0f) - (m_renderTargetSize.y / 2.0f);
	int32_t xe = mapCentreX + (m_cameraPosition.x / 50.0f) + (m_renderTargetSize.x / 2.0f);
	int32_t ye = mapCentreY + (m_cameraPosition.y / 50.0f) + (m_renderTargetSize.y / 2.0f);
	if (xs < 0)xs = 0;
	m_borders[0] = xs;
	if (ys < 0)ys = 0;
	m_borders[1] = ys;
	if (xe >= m_xSize)xe = m_xSize - 1;
	m_borders[2] = xe;
	if (ye >= m_ySize)ye = m_ySize - 1;
	m_borders[3] = ye;

	
	
}



void GameRenderer::Render()
{
	SetStroke(1.0f);
	SetBrush(m_lightSlateGrayBrush);
	SetTextSize(30.0f);




	for (int32_t x = m_borders[0]; x < m_borders[2]; x++)
	{
		for (int32_t y = m_borders[1]; y < m_borders[3]; y++)
		{

				DirectX::XMFLOAT2 pt = m_gameMap[x][y]->position;
				DrawRectangle({ m_cameraPosition.x+(50.0f*x),m_cameraPosition.y+(50.0f*y),m_cameraPosition.x + 50.0f*(x+1),m_cameraPosition.y+(50.0f*(y+1))});
		}
	}

	SetBrush(m_cornflowerBlueBrush);
	ef = clock();

	deltaTime += ef - bf;
	frames++;

	if (clockToMilliseconds(deltaTime) > 1000.0) {
		frameRate = (double)frames*0.5 + frameRate * 0.5;
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

		__fps = (int)(1000 / averageFrameTimeMilliseconds);


	}
	DrawWideText(std::to_wstring(__fps), {10.0f,10.0f,200.0f,50.0f});
}
