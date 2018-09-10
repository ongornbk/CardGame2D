#include "stdafx.h"
#include "GameMapComponent.h"


Tile* GameMapComponent::m_gameMap[128][20] = {};
int32_t GameMapComponent::m_borders[4] = { 0u,0u,0u,0u };