#pragma once
#include "RendererManager.h"

class GameRenderer : RendererManager,RenderTargetSize
{
public:
	GameRenderer();
	~GameRenderer();

	void Update();
	void Render();
};

