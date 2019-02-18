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
	EXPLODE = 3
};

struct CellS
{

	bool        hover;
	CellStance  stance;
	CellStance2 stance2;
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

