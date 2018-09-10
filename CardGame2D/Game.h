#pragma once
#include "GameRenderer.h"
#include "GameMap.h"

class Game
{
public:
	Game();
	~Game();

	Boolean Initialize();

private:
	GameRenderer m_renderer;
	GameMap*     m_gameMap;
};

