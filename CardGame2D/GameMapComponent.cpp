#include "stdafx.h"
#include "GameMapComponent.h"


Tile* GameMapComponent::m_gameMap[GAMEMAP_SIZEX][GAMEMAP_SIZEY] = {};
int32_t GameMapComponent::m_borders[4] = { 0u,0u,0u,0u };