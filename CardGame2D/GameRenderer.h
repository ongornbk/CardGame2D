#pragma once
#include "RendererManager.h"
#include "CameraPositionComponent.h"
#include "InputComponent.h"
#include "WindowHandle.h"

#define CELL_SIZE_FLOAT 16.f
#define CELL_SIZE       int(16)



enum CellStance
{
	EMPTY = 0,
	MINE = 1
};

enum CellStance2
{
	NONE = 0,
	FLAG = 1,
	QUESTION_MARK = 2,
	EXPLODE = 3,
	REVEALED = 4
};

struct CellS
{

	bool        hover;
	CellStance  stance;
	CellStance2 stance2;
	int8_t      mines{};

	void reveal(CellS matrix[CELL_SIZE][CELL_SIZE], int x, int y)
	{
		if (stance2 == CellStance2::NONE)
		{
			if (stance == CellStance::MINE)
			{
				stance2 = CellStance2::EXPLODE;
			}
			else
			{
				stance2 = CellStance2::REVEALED;
				if (mines == 0)
				{



					{
						if (x > 0)
						{
							if (y > 0)
							{
								matrix[x - 1][y - 1].reveal(matrix, x - 1, y - 1);
								matrix[x][y - 1].reveal(matrix, x, y - 1);
								matrix[x - 1][y].reveal(matrix, x - 1, y);
								if (y < (CELL_SIZE - 1))
								{
									matrix[x - 1][y + 1].reveal(matrix, x - 1, y + 1);
									matrix[x][y + 1].reveal(matrix, x, y + 1);
								}
								if (x < (CELL_SIZE - 1))
								{
									matrix[x + 1][y - 1].reveal(matrix, x + 1, y - 1);
									matrix[x + 1][y].reveal(matrix, x + 1, y);
									if (y < (CELL_SIZE - 1))
										matrix[x + 1][y + 1].reveal(matrix, x + 1, y + 1);
								}

							}
							else
							{
								matrix[x - 1][y].reveal(matrix, x - 1, y);
								matrix[x - 1][y + 1].reveal(matrix, x - 1, y + 1);
								matrix[x][y + 1].reveal(matrix, x, y + 1);
								if (x < (CELL_SIZE - 1))
								{
									matrix[x + 1][y + 1].reveal(matrix, x + 1, y + 1);
									matrix[x + 1][y].reveal(matrix, x + 1, y);
								}
							}
						}
						else
						{
							if (y > 0)
							{
								matrix[x][y - 1].reveal(matrix, x, y - 1);
								matrix[x + 1][y - 1].reveal(matrix, x + 1, y - 1);
								matrix[x + 1][y].reveal(matrix, x + 1, y);
								if (y < (CELL_SIZE - 1))
								{
									matrix[x + 1][y + 1].reveal(matrix, x + 1, y + 1);
									matrix[x][y + 1].reveal(matrix, x, y + 1);
								}
							}
							else
							{
								matrix[x][y + 1].reveal(matrix, x, y + 1);
								matrix[x + 1][y + 1].reveal(matrix, x + 1, y + 1);
								matrix[x + 1][y].reveal(matrix, x + 1, y);
							}
						}
					}




				}
			}
		}
	}

	void flag()
	{
		if (stance2 == CellStance2::NONE)
			stance2 = CellStance2::FLAG;
		else if (stance2 == CellStance2::FLAG)
			stance2 = CellStance2::NONE;
	}

};

class GameRenderer : RendererManager,RenderTargetSize,InputComponent, WindowHandle
{
public:
	GameRenderer();
	~GameRenderer();

	void Update();
	void Render();

private:
	CellS matrix[CELL_SIZE][CELL_SIZE];
};

