#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"
#include "Timer.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <random>

#define TILE_SIZE 50.0f

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

		int8_t Random8(int8_t min, int8_t max)
		{
			return min + rand() % ((max + 1) - min);
		}
	}
}

GameRenderer::GameRenderer() : RendererManager(&updateFoo, &renderFoo)
{
	ZeroMemory(&matrix, sizeof(int8_t) * CELL_SIZE * CELL_SIZE);
	for (int16_t x = 1; x < CELL_SIZE - 1; x++)
	{
		for (int16_t y = 1; y < CELL_SIZE - 1; y++)
		{
			int8_t r = Random8(0, 4);
			if (!r) matrix[x][y] = 1;
		}
	}
	m_instance = this;
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

	
	
}



void GameRenderer::Render()
{

	bf = clock();

	SetStroke(1.0f);
	SetBrush(m_lightSlateGrayBrush);
	SetTextSize(30.0f);


	int32_t summc = 0;

	for (int16_t x = 1; x < CELL_SIZE-1; x++)
	{
		for (int16_t y = 1; y < CELL_SIZE-1; y++)
		{
			if (matrix[x][y])
			{
				summc++;
				int8_t sum = 0;

				if (matrix[x - 1][y])sum++;
				if (matrix[x - 1][y - 1])sum++;
				if (matrix[x - 1][y + 1])sum++;
				if (matrix[x + 1][y + 1])sum++;
				if (matrix[x + 1][y - 1])sum++;
				if (matrix[x + 1][y])sum++;
				if (matrix[x][y+1])sum++;
				if (matrix[x][y-1])sum++;
				if (sum > Random8(5,6)||sum < Random8(2,3))
				{
					matrix[x][y] = 0;
				}
				else
				{

					if (sum < Random8(1,5)||matrix[x][y]<Random8(1,3))
					{
						int8_t r = Random8(0, 8);
						switch (r)
						{
						case 0: matrix[x - 1][y] = sum;		  break;
							case 1: matrix[x - 1][y - 1]= sum;	  break;
							case 2: matrix[x - 1][y + 1]= sum;	  break;
							case 3: matrix[x + 1][y + 1]= sum;	  break;
							case 4: matrix[x + 1][y - 1]= sum;	  break;
							case 5: matrix[x + 1][y]= sum;	  break;
							case 6: matrix[x][y + 1]= sum;	  break;
							case 7: matrix[x][y - 1]= sum;	  break;
						}
					}
					matrix[x][y] = sum;
					switch (sum)
					{
					case 2:
						SetBrush(m_orangeBrush);
						break;
					case 3:
						SetBrush(m_redBrush);
						break;
					
					default:
						SetBrush(m_lightSlateGrayBrush);
					}
					FillRectangle({ float(x - 1)*(m_renderTargetSize.x / CELL_SIZE_FLOAT),float(y - 1)*(m_renderTargetSize.y / CELL_SIZE_FLOAT),float(x)*(m_renderTargetSize.x / CELL_SIZE_FLOAT) ,float(y)*(m_renderTargetSize.y / CELL_SIZE_FLOAT) });
				}
			}
		}
	}

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
	SetBrush(m_cornflowerBlueBrush);
	DrawWideText(std::to_wstring(__fps), {10.0f,0.0f,200.0f,50.0f});
	DrawWideText(std::to_wstring(summc), { 10.0f,80.0f,200.0f,50.0f });

}
