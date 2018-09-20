#pragma once
#include "RendererManager.h"
#include "CameraPositionComponent.h"
#include "InputComponent.h"

#define CELL_SIZE_FLOAT 128.0f
#define CELL_SIZE       int(128)

class GameRenderer : RendererManager,RenderTargetSize,CameraPositionComponent,InputComponent
{
public:
	GameRenderer();
	~GameRenderer();

	void Update();
	void Render();

private:
	int8_t matrix[CELL_SIZE][CELL_SIZE];
};

