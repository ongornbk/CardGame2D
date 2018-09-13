#pragma once
#include "GameMapComponent.h"
#include "Brushes.h"
#include <DirectXMath.h>




class GameMapSize
{
protected:

	static uint16_t m_xSize;
	static uint16_t m_ySize;
};

class GameMap : GameMapSize,GameMapComponent,Brushes
{
public:
	~GameMap();
	static GameMap* CreateGameMap();

private:
	GameMap();
};


