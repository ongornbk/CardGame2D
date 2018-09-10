#pragma once
#include "RendererManager.h"
#include "GameMap.h"
#include "CameraPositionComponent.h"

class GameRenderer : RendererManager,RenderTargetSize,GameMapComponent,GameMapSize,CameraPositionComponent
{
public:
	GameRenderer();
	~GameRenderer();

	void Update();
	void Render();
};

