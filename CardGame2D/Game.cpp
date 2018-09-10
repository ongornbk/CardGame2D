#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	m_gameMap = nullptr;
}


Game::~Game()
{
	if (m_gameMap)
	{
		delete m_gameMap;
		m_gameMap = nullptr;
	}
}

Boolean Game::Initialize()
{
	m_gameMap = GameMap::CreateGameMap();
	return (Boolean)m_gameMap;
}
