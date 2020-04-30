#include "stdafx.h"
#include "GameRenderer.h"
#include "Graphics.h"
#include "Timer.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <random>

namespace
{
	GameRenderer* m_instance = nullptr;

	_Use_decl_annotations_
	static void _stdcall renderFoo() noexcept
	{
		m_instance->Render();
	}

	_Use_decl_annotations_
	static void _stdcall updateFoo() noexcept
	{
		m_instance->Update();
	}

	constexpr float MARGIN_LEFT = 50.f;
	constexpr float MARGIN_RIGHT = 50.f;
	constexpr float MARGIN_BOTTOM = 20.f;
	constexpr float MARGIN_TOP = 100.f;

	static float XSIZE;
	static float YSIZE;

	static float  margin_left;
	static float  margin_right;
	static float  margin_bottom;
	static float  margin_top;

	POINT mouseC;
	POINT last;

}




GameRenderer::~GameRenderer()
{
}

namespace
{
	clock_t deltaTime = 0;
	uint64_t frames = 0;
	double  frameRate = 30;
	double  averageFrameTimeMilliseconds = 33.333;
	clock_t bf;
	clock_t ef;
	uint64_t __fps = 0;

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

	srand(1234u);
	ZeroMemory(&matrix, sizeof(CellS) * CELL_SIZE * CELL_SIZE);

#pragma omp parallel for schedule(dynamic)
	for (int16_t x = 0; x < CELL_SIZE - 1; x++)
	{
		for (int16_t y = 0; y < CELL_SIZE - 1; y++)
		{
			if (Random8(0, 100)<20)
			{
				matrix[x][y].stance = CellStance::MINE;
				matrix[x][y].stance2 = CellStance2::NONE;

				if (x > 0)
				{
					if (y > 0)
					{
						matrix[x - 1][y - 1].mines++;
						matrix[x][y - 1].mines++;
						matrix[x - 1][y].mines++;
						if (y < (CELL_SIZE - 1))
						{
							matrix[x - 1][y + 1].mines++;
							matrix[x][y + 1].mines++;
						}
						if (x < (CELL_SIZE - 1))
						{
							matrix[x + 1][y - 1].mines++;
							matrix[x + 1][y].mines++;
							if (y < (CELL_SIZE - 1))
							matrix[x + 1][y + 1].mines++;
						}

					}
					else
					{
						matrix[x - 1][y].mines++;
						matrix[x - 1][y+1].mines++;
						matrix[x][y + 1].mines++;
						if (x < (CELL_SIZE - 1))
						{
							matrix[x + 1][y + 1].mines++;
							matrix[x + 1][y].mines++;
						}
					}
				}
				else
				{
					if (y > 0)
					{
						matrix[x][y - 1].mines++;
						matrix[x + 1][y - 1].mines++;
						matrix[x + 1][y].mines++;
						if (y < (CELL_SIZE - 1))
						{
							matrix[x +1][y + 1].mines++;
							matrix[x][y + 1].mines++;
						}
					}
					else
					{
						matrix[x][y + 1].mines++;
						matrix[x + 1][y +1].mines++;
						matrix[x + 1][y].mines++;
					}
				}

			}
			matrix[x][y].stance2 = CellStance2::NONE;
		}
	}

	m_instance = this;
}

void GameRenderer::Update()
{
	bf = clock();
	Timer::Update();


	GetCursorPos(&mouseC);
	ScreenToClient(m_windowHandle, &mouseC);

	matrix[last.x][last.y].hover = false;
		
		mouseC.x -= margin_left;
		mouseC.x /= XSIZE;
	if (mouseC.x >= CELL_SIZE)mouseC.x = CELL_SIZE - 1; else if (mouseC.x < 0) mouseC.x = 0;

	mouseC.y -= margin_top;
	mouseC.y /= YSIZE;

	

	if (mouseC.y >= CELL_SIZE)mouseC.y = CELL_SIZE - 1; else if (mouseC.y < 0) mouseC.y = 0;

	CellS &cell = matrix[mouseC.x][mouseC.y];
	cell.hover = true;

	last = mouseC;

	//

	const bool lclick = m_input->GetMousePressed(0);
	const bool rclick = m_input->GetMousePressed(1);

	if (lclick)
	{
		

		int x = mouseC.x;
		int y = mouseC.y;

		cell.reveal(matrix, x, y);

		
	}
	else
	{
		if (rclick)
		{
			cell.flag();
		}
	}


}


void GameRenderer::Render()
{

	
	SetTextSize(30.0f);

	margin_left  = MARGIN_LEFT;
	margin_right  = MARGIN_RIGHT;
	margin_bottom  = MARGIN_BOTTOM;
	margin_top  = MARGIN_TOP;

	XSIZE = (m_renderTargetSize.x - margin_left - margin_right) / CELL_SIZE;
	YSIZE = (m_renderTargetSize.y - margin_top - margin_bottom) / CELL_SIZE;

	const float XSIZE_old = XSIZE;
	const float YSIZE_old = YSIZE;

	if (XSIZE > YSIZE)
	{
		XSIZE = YSIZE;
		margin_left += ((XSIZE_old - XSIZE) * (CELL_SIZE_FLOAT / 2.f));
	}
	else
	{
		YSIZE = XSIZE;
		margin_top += ((YSIZE_old - YSIZE) * (CELL_SIZE_FLOAT / 2.f));
	}
		

	
	for (int x = 0; x < CELL_SIZE; x++)
	{
		for (int y = 0; y < CELL_SIZE; y++)
		{
			
			const CellS& cell = matrix[x][y];

			const DirectX::XMFLOAT4 pos = DirectX::XMFLOAT4(margin_left + XSIZE * x, margin_top + YSIZE * y, margin_left + XSIZE * (x + 1), margin_top + YSIZE * (y + 1));

			switch (cell.stance2)
			{
			case CellStance2::NONE:
			{
				if (cell.hover)
				{
					SetStroke(2.f);
					SetBrush(m_orangeBrush);
					DrawRectangle(pos);
				}
				else
				{
							SetStroke(1.f);
							SetBrush(m_lightSlateGrayBrush);
							DrawRectangle(pos);
				}

				
				
				break;
			}
			case CellStance2::EXPLODE:
			{
				SetBrush(m_redBrush);
				FillRectangle(pos);
				break;
			}
			case CellStance2::REVEALED:
			{
				SetBrush(m_cornflowerBlueBrush);
				FillRectangle(pos);
				SetBrush(m_blackBrush);
				DrawWideText(std::to_wstring(cell.mines), pos);
				break;
			}
			case CellStance2::FLAG:
			{
				SetBrush(m_orangeBrush);
				FillRectangle(pos);
				break;
			}

			}
		}
	}

	SetBrush(m_orangeBrush);
	SetStroke(2.f);
	DrawRectangle(DirectX::XMFLOAT4(margin_left -1.f, margin_top - 1.f, margin_left + XSIZE * (CELL_SIZE) + 1.f, margin_top + YSIZE * (CELL_SIZE) + 1.f));
	
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
	DrawWideText(std::to_wstring(__fps) + L" FPS", {10.0f,0.0f,200.0f,50.0f});
	DrawWideText(std::to_wstring(mouseC.x), { 10.0f,50.0f,200.0f,50.0f });
	DrawWideText(std::to_wstring(mouseC.y), { 10.0f,100.0f,200.0f,50.0f });

}
