#pragma once
#include "Graphics.h"


class RendererManager : public Graphics
{
public:

	void Update();
	void Render();

public:
	RendererManager(void (*Render)(void));
	~RendererManager();
protected:
	float    m_deltaTime;
};

