#pragma once
#include "Tile.h"

class GameMapComponent
{
protected:
	static Tile* m_gameMap[256][25];
	static int32_t m_borders[4];
};

