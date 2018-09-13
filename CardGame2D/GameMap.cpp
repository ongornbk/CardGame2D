#include "stdafx.h"
#include "GameMap.h"

uint16_t GameMapSize::m_xSize = 128u;
uint16_t GameMapSize::m_ySize = 20u;

GameMap::GameMap()
{
}


GameMap::~GameMap()
{

	for (uint16_t x = 0u; x < m_xSize; x++)
	{
		for (uint16_t y = 0u; y < m_ySize; y++)
		{

			delete m_gameMap[x][y];
			m_gameMap[x][y] = nullptr;
		}
	}

	
}

GameMap * GameMap::CreateGameMap()
{
	GameMap* map = new GameMap();
	for (uint16_t x = 0u; x < m_xSize; x++)
	{
		for (uint16_t y = 0u; y < m_ySize; y++)
		{
			m_gameMap[x][y] = new Tile();
			m_gameMap[x][y]->position = {(float)(x)*10,(float)(y)*10};
			m_gameMap[x][y]->m_brush = (void*)m_cornflowerBlueBrush;
		}
	}
	return map;
}
