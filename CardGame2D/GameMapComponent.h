#pragma once
#include "Tile.h"

class GameMapComponent
{
protected:
	static Tile* m_gameMap[GAMEMAP_SIZEX][GAMEMAP_SIZEY];
	static int32_t m_borders[4];
};

