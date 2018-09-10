#pragma once
#include "Tile.h"

class GameMapComponent
{
protected:
	static Tile* m_gameMap[128][20];
	static int32_t m_borders[4];
};

