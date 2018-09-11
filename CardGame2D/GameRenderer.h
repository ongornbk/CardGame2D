#pragma once
#include "RendererManager.h"
#include "GameMap.h"
#include "CameraPositionComponent.h"
#include "InputComponent.h"

class GameRenderer : RendererManager,RenderTargetSize,GameMapComponent,GameMapSize,CameraPositionComponent,InputComponent
{
public:
	GameRenderer();
	~GameRenderer();

	void Update();
	void Render();
};

