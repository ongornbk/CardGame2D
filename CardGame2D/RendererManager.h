#pragma once
#include "Graphics.h"

class RendererManager : public Graphics
{
public:

	void Update();
	void Render();

public:
	RendererManager(void(*Update)(void),void (*Render)(void));
	~RendererManager();

protected:
};

