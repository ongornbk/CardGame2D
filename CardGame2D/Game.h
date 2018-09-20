#pragma once
#include "GameRenderer.h"

class Game
{
public:
	Game();
	~Game();

	Boolean Initialize();

private:
	GameRenderer m_renderer;

	
};

